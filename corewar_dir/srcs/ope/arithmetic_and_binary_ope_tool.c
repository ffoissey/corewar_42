/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_and_binary_ope_tool.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:07:18 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/22 15:48:39 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	process_op(t_carriages *current, enum e_type type, int32_t *arg)
{
	int32_t		reg_val;
	uint8_t		flag_reg;

	flag_reg = SET | GET;
	if (type == OP_AND)
		reg_val = set_reg_value(current, (int8_t)arg[2], arg[0] & arg[1], &flag_reg);
	else if (type == OP_OR)
		reg_val = set_reg_value(current, (int8_t)arg[2], arg[0] | arg[1], &flag_reg);
	else if (type == OP_XOR)
		reg_val = set_reg_value(current, (int8_t)arg[2], arg[0] ^ arg[1], &flag_reg);
	else if (type == OP_ADD)
		reg_val = set_reg_value(current, (int8_t)arg[2], arg[0] + arg[1], &flag_reg);
	else if (type == OP_SUB)
		reg_val = set_reg_value(current, (int8_t)arg[2], arg[0] - arg[1], &flag_reg);
	else
		return (FAILURE);
	if (flag_reg == BAD_REG)
		return (FAILURE);
	current->carry = (reg_val == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}

int8_t			do_op(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[3];

	arg[0] = get_arg(current, data, START_ARG | BIG_DIR | IND, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, BIG_DIR | IND, &type);
	arg[2] = get_arg(current, data, END_ARG | REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	return (process_op(current, type, arg));
}
