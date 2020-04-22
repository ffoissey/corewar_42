/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ope_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:37:27 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/22 15:32:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t	load_value(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[2];
	int32_t		reg_val;
	uint8_t		flag_reg;
	uint8_t		ocp;

	ocp = core_get_ocp(data, current->position + 1);
	arg[0] = get_arg(current, data,
			START_ARG | IND_NUM | BIG_DIR, &type);
	if (type == NO_OP)
		return (FAILURE);
	if (((ocp >> 6) & 0x03) == T_IND)
	{
		if (type == OP_LD)
			arg[0] %= IDX_MOD;
		arg[0] = get_ind_value(data, current->position, get_pos(arg[0]), IND);
	}
	arg[1] = get_arg(current, data, END_ARG | REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	flag_reg = SET | GET;
	reg_val = set_reg_value(current, arg[1], arg[0], &flag_reg);
	if (flag_reg == BAD_REG)
		return (FAILURE);
	current->carry = (reg_val == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}

int8_t	load_indvalue(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[3];
	uint8_t		flag_reg;
	int16_t		pos;
	int32_t		to_load;

	flag_reg = (type == OP_LLDI) ? IND : IND_LLD;
	arg[0] = get_arg(current, data, START_ARG | SMALL_DIR | flag_reg, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, SMALL_DIR, &type);
	arg[2] = get_arg(current, data, END_ARG | REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	pos = arg[0] + arg[1];
	if (type == OP_LDI)
		pos %= IDX_MOD;
	to_load = get_ind_value(data, current->position, get_pos(pos), IND);
	flag_reg = SET;
	set_reg_value(current, arg[2], to_load, &flag_reg);
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}
