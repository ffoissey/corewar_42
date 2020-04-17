/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:17:51 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 11:37:30 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	do_bin_op(t_carriages *current, t_data *data, uint8_t ope)
{
	int32_t		args[3];
	int16_t		reg_value;
	uint8_t		flag_reg;

	current->carry = CARRY_OFF;
	args[0] = get_arg(current, data, 1, NO_NEED);
	args[1] = get_arg(current, data, 2, NO_NEED);
	args[2] = get_arg(current, data, 3, NO_NEED);
	flag_reg = SET;
	if (ope & BIN_AND)
		reg_val = set_reg_value(current, args[2], args[0] & args[1], &flag_reg);
	else if (ope & BIN_OR)
		reg_val = set_reg_value(current, args[2], args[0] | args[1], &flag_reg);
	else if (ope & BIN_XOR
		reg_val = set_reg_value(current, args[2], args[0] ^ args[1], &flag_reg);
	if (flag != BAD_REG && rev_val == 0)
		current->carry = CARRY_ON;
	return (SUCCESS);
}

/*
*** AND 0x06
*/

int8_t			ope_and(t_carriages *current, t_data *data)
{
	return (do_bin_op(current, data, BIN_AND);
}

/*
*** OR 0x07
*/

int8_t			ope_or(t_carriages *current, t_data *data)
{
	return (do_bin_op(current, data, BIN_OR);
}

/*
*** XOR 0x08
*/

int8_t			ope_xor(t_carriages *current, t_data *data)
{
	return (do_bin_op(current, data, BIN_XOR);
}
