/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:22:25 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/16 21:23:00 by ffoissey         ###   ########.fr       */
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

	i = 0;
	max = (flag & IND) ? 4 : 2;
	while (i < max)
	{
		value |= (uint8_t)data->vm.arena[get_pos(position + i + arg)]; // position + TO_JMP ? 
		value << 8;
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

int8_t		core_get_reg(t_data *data, int16_t position, t_carriages *current)
{
	int8_t		reg;

	reg = (data->vm.arena[get_pos(position)]);
	if (reg > 0 && reg <= REG_NUMBER)
		return (current->registres[reg - 1]);
	return (FAILURE); // exit
}

int32_t		get_arg(t_carriages *current, t_data *data, uint8_t arg_nb,
				uint16_t flag)
{
	static int8_t	ocp = 0;
	static int8_t	mask;
	int32_t			arg;

	if (arg_nb == 1)
	{
		current->to_jump += MEM_OP_CODE;
		if ((flag & NO_OCP) == FALSE)
		{
			current->to_jump += MEM_OCP;
			ocp = core_get_ocp(data, current->position + current->to_jump);
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
	arg = FAILURE;
	if (mask == T_REG)
	{
		arg = core_get_reg(data, current->position + current->to_jump, current);
		if (arg < 0)
			exit(1); // gerer quand c'est negatif
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
	else
		exit(1); // ATTENTION
	return (arg);	
}
