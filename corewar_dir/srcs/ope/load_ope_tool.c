/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ope_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:37:27 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 20:52:27 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t	load_value(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[2];
	int16_t		reg_val;
	uint8_t		flag_reg;

	current->carry = CARRY_OFF;
	arg[0] = get_arg(current, data,
			INIT_ARG | IND | BIG_DIR, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	flag_reg = SET | GET;
	reg_val = set_reg_value(current, arg[1], arg[0], &flag_reg);
	if (flag_reg != BAD_REG && reg_val == 0)
		current->carry = CARRY_ON;
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}

int8_t	load_indvalue(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[3];
	uint8_t		flag_reg;
	int16_t		pos;
	int16_t		to_load;

	arg[0] = get_arg(current, data,
			INIT_ARG | SMALL_DIR | (type == OP_LDI) ? IND : IND_LLD, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, SMALL_DIR, &type);
	arg[2] = get_arg(current, data, REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	pos = get_pos(arg[0] + arg[1]);
	if (type == OP_LDI)
		pos %= IDX_MOD;
	to_load = get_ind_value(data, current->position, pos, IND);
	flag_reg = SET;
	set_reg_value(current, arg[2], to_load, &flag_reg);
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}
