/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:22:25 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 15:32:33 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint8_t		core_get_ocp(t_data *data, int16_t position)
{
	return (data->vm.arena[get_pos(position)]);
}

int32_t		core_get_dir(t_data *data, int16_t position, uint16_t flag)
{
	int32_t		dir;

	if (flag & SMALL_DIR)
	{
		dir = (data->vm.arena[position % MEM_SIZE] << 8
			| data->vm.arena[(position + 1) % MEM_SIZE]);
		return (dir);
	}
	else
	{
		dir = (data->vm.arena[position % MEM_SIZE] << 24
			| data->vm.arena[(position + 1) % MEM_SIZE] << 16
			| data->vm.arena[(position + 2) % MEM_SIZE] << 8
			| data->vm.arena[(position + 3) % MEM_SIZE]);
	}
	return (dir);
}

int16_t		get_ind_value(t_data *data, int16_t position, int32_t arg,
					uint16_t flag)
{
	uint8_t		i;
	uint8_t		max;
	int32_t		value;
	int64_t		add;

	i = 0;
	max = (flag & IND) ? 4 : 2;
	while (i < max)
	{
		add = ((uint8_t)data->vm.arena[get_pos(position + i + arg)]);
		add <<= (8 * i) ; // position + TO_JMP ? 
		value |= (int32_t)add;
		i++;
	}
	return (value);
}

int16_t		core_get_ind(t_data *data, int16_t position, int16_t to_jump,
				uint16_t flag)
{
	int16_t		ind;
	int16_t		jump_pos;

	jump_pos = get_pos(position + to_jump);
	ind = (data->vm.arena[jump_pos] << 8 | data->vm.arena[get_pos(jump_pos + 1)]);
	return (get_ind_value(data, position, ind % IDX_MOD, flag));
}

int16_t		set_reg_value(t_carriages *current, int8_t reg, uint8_t value,
				uint8_t *flag)
{
	if (reg > 0 && reg <= REG_NUMBER)
	{
		if (*flag & SET)
			current->registres[reg - 1] = value;
		return (current->registres[reg - 1]);
	}
	*flag = BAD_REG;
	return (FAILURE);
}

int8_t		core_get_reg(t_data *data, int16_t position, t_carriages *current)
{
	int8_t		reg;

	reg = (data->vm.arena[get_pos(position)]);
	if (reg > 0 && reg <= REG_NUMBER)
		return (current->registres[reg - 1]);
	return (FAILURE); // exit
}


static int32_t	find_arg(t_carriages *current, t_data *data, uint16_t flag,
					int8_t mask)
{
	int32_t			arg;

	arg = 0;
	if (mask == T_REG)
	{
		arg = core_get_reg(data, current->position + current->to_jump, current);
		current->to_jump += MEM_REG;
	}
	else if  (mask == T_DIR)
	{
		arg = core_get_dir(data, current->position + current->to_jump, flag);
		current->to_jump += (flag == SMALL_DIR) ? MEM_SMALL_DIR : MEM_DIR;
	}
	else if  (mask == T_IND)
	{
		arg = core_get_ind(data, current->position, current->to_jump, flag);
		current->to_jump += MEM_IND;
	}
	return (arg);	
}

static int8_t		ocp_verification(uint8_t ocp, enum e_type type)
{
	static const uint16_t mask_tab[] = {MASK_LIVE, MASK_LD, MASK_ST, MASK_ADD,
									MASK_SUB, MASK_AND, MASK_OR, MASK_XOR,
									MASK_ZJMP, MASK_LDI, MASK_STI, MASK_FORK,
									MASK_LLD, MASK_LLDI, MASK_LFORK, MASK_AFF};
	uint16_t	mask;

	mask = 0;
	mask |= (ocp & 0b00000011);
	mask |= ((ocp & 0b00001100) << 4);
	mask |= ((ocp & 0b00110000) << 8);
	mask |= ((ocp & 0b11000000) << 12);
	ft_printf("mask = %#.16b\ngood = %#.16b\n\n", mask, mask_tab[type]);
	if (mask_tab[type] & (mask ^ mask_tab[type]))
		return (FAILURE);
	return (SUCCESS);
}

int32_t			get_arg(t_carriages *current, t_data *data, uint16_t flag,
					enum e_type *type)
{
	static uint8_t	ocp = 0;
	static uint8_t	arg_nb = 1;
	uint8_t			mask;

	if (type == NO_OP)
		return (FAILURE);
	if (flag & INIT_ARG)
		arg_nb = 1;
	if (arg_nb == 1)
	{
		current->to_jump += MEM_OP_CODE;
		if ((flag & NO_OCP) == FALSE)
		{
			current->to_jump += MEM_OCP;
			ocp = core_get_ocp(data, current->position + current->to_jump);
			if (ocp_verification(ocp, *type) == FAILURE)
			{
				*type = NO_OP;
				return (FAILURE); 
			}
		}
	}
	if (flag & NO_OCP)
		mask = flag >> 8;
	else
	{
		mask = ocp;
		mask >>= ((arg_nb - 1) * 2);
		mask &= 0b00000011;
	}
	arg_nb++;
	return (find_arg(current, data, flag, mask));
}
