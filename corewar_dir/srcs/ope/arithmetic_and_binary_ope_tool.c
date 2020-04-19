/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_and_binary_ope_tool.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:07:18 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/19 18:38:02 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			do_op(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t	arg[3];
	int16_t		reg_val;
	uint8_t		flag_reg;

	current->carry = CARRY_OFF;
	arg[0] = get_arg(current, data, START_ARG | BIG_DIR | IND, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, BIG_DIR | IND, &type);
	arg[2] = get_arg(current, data, END_ARG | REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	flag_reg = SET | GET;
	if (type == OP_AND)
		reg_val = set_reg_value(current, arg[2], arg[0] & arg[1], &flag_reg);
	else if (type == OP_OR)
		reg_val = set_reg_value(current, arg[2], arg[0] | arg[1], &flag_reg);
	else if (type == OP_XOR)
		reg_val = set_reg_value(current, arg[2], arg[0] ^ arg[1], &flag_reg);
	else if (type == OP_ADD)
		reg_val = set_reg_value(current, arg[2], arg[0] + arg[1], &flag_reg);
	else if (type == OP_SUB)
		reg_val = set_reg_value(current, arg[2], arg[0] - arg[1], &flag_reg);
	if (flag_reg != BAD_REG && reg_val == 0)
		current->carry = CARRY_ON;
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}
