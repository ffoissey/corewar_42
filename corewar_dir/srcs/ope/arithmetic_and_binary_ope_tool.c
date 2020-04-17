/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_and_binary_ope_tool.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:07:18 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 12:37:56 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			do_op(t_carriages *current, t_data *data, uint8_t ope)
{
	int32_t		arg[3];
	int16_t		reg_val;
	uint8_t		flag_reg;

	current->carry = CARRY_OFF;
	arg[0] = get_arg(current, data, 1, NO_NEED);
	arg[1] = get_arg(current, data, 2, NO_NEED);
	arg[2] = get_arg(current, data, 3, NO_NEED);
	flag_reg = SET | GET;
	if (ope & BINARY_AND)
		reg_val = set_reg_value(current, arg[2], arg[0] & arg[1], &flag_reg);
	else if (ope & BINARY_OR)
		reg_val = set_reg_value(current, arg[2], arg[0] | arg[1], &flag_reg);
	else if (ope & BINARY_XOR)
		reg_val = set_reg_value(current, arg[2], arg[0] ^ arg[1], &flag_reg);
	else if (ope & BINARY_XOR)
		reg_val = set_reg_value(current, arg[2], arg[0] ^ arg[1], &flag_reg);
	else if (ope & ARITHMETIC_ADD)
		reg_val = set_reg_value(current, arg[2], arg[0] + arg[1], &flag_reg);
	else if (ope & ARITHMETIC_SUB)
		reg_val = set_reg_value(current, arg[2], arg[0] - arg[1], &flag_reg);
	if (flag_reg != BAD_REG && reg_val == 0)
		current->carry = CARRY_ON;
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}
