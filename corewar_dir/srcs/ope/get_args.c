/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:22:25 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 18:34:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int32_t	find_arg(t_carriages *current, t_data *data, uint16_t *flag,
					uint8_t mask)
{
	int32_t			arg;

	arg = 0;
	if (mask == T_REG)
	{
		arg = core_get_reg(data, current->position + current->to_jump, current);
		if (arg == FAILURE)
			*flag |= BAD_REG; 
		else if ((*flag & REG_NUM) == FALSE)
		{
			*flag = GET;
			arg = set_reg_value(current, arg, NO_NEED, (uint8_t *)flag);
		}
		current->to_jump += MEM_REG;
	}
	else if  (mask == T_DIR)
	{
		arg = core_get_dir(data, current->position + current->to_jump, *flag);
		current->to_jump += (*flag == SMALL_DIR) ? MEM_SMALL_DIR : MEM_DIR;
	}
	else if  (mask == T_IND)
	{
		arg = core_get_ind(data, current->position, current->to_jump, *flag);
		current->to_jump += MEM_IND;
	}
	return (arg);	
}

static int8_t		ocp_verification(uint8_t ocp, enum e_type type)
{
	static const uint16_t mask_tab[] = {0x00, MASK_LIVE, MASK_LD, MASK_ST,
									MASK_ADD, MASK_SUB, MASK_AND, MASK_OR,
									MASK_XOR, MASK_ZJMP, MASK_LDI, MASK_STI,
									MASK_FORK, MASK_LLD, MASK_LLDI, MASK_LFORK,
									MASK_AFF};
	uint16_t	mask;
	uint16_t	tmp_mask;
	uint8_t		i;

	mask = ((ocp & 0xc0) << 12);
	i = 0;
	while (i < 3)
	{
		tmp_mask = ocp & (0x03 << (i * 2));
		if (tmp_mask == (T_IND << (i * 2)))
			mask |= (MASK_IND << (i * 4));
		else if (tmp_mask == (T_DIR << (i * 2)))
			mask |= (MASK_DIR << (i * 4));
		else if (tmp_mask == (T_REG << (i * 2)))
			mask |= (MASK_REG << (i * 4));
		i++;
	}
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
	int32_t			arg;

	if (type == NO_OP)
		return (FAILURE);
	if (flag & INIT_ARG)
		arg_nb = 1;
	if (arg_nb == 1)
	{
		current->to_jump = MEM_OP_CODE;
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
	{
		flag &= ~INIT_ARG;
		mask = flag >> 8;
	}
	else
	{
		mask = ocp;
		mask >>= ((arg_nb - 1) * 2);
		mask &= 0x03;
	}
	arg_nb++;
	arg = find_arg(current, data, &flag, mask);
	if (flag & BAD_REG)
		*type = NO_OP;
	return (arg);
}
