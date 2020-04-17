/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:26:15 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 12:26:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void store_value(t_data *data, int16_t position, int16_t reg_value)
{
	core_put_reg_ind(data, get_pos(position) % IDX_MOD, reg_value);
}

/*
**** ST 0x03
*/

int8_t			ope_st(t_carriages *current, t_data *data)
{
	int32_t		arg[2];
	int16_t		reg_value;
	uint8_t		flag;
	uint8_t		ocp;

	ocp = core_get_ocp(data, current->position + current->to_jump);
	arg[0] = get_arg(current, data, 1, NO_NEED);
	arg[1] = get_arg(current, data, 2, IND);
	flag = SET;
	if (ocp == REG_REG_)
		set_reg_value(current, arg[1], arg[0], &flag);
	if (flag == BAD_REG)
		return (FAILURE);
	flag = GET;
	reg_value = set_reg_value(current, arg[0], NO_NEED, &flag);
	if (flag == BAD_REG)
		return (FAILURE);
	store_value(data, get_pos(current->position) + arg[1], reg_value);
	return (SUCCESS);
}

/*
**** STI 0x0b
*/

int8_t			ope_sti(t_carriages *current, t_data *data)
{
	int32_t		arg[3];
	int16_t		reg_value;
	uint8_t		flag;

	arg[0] = get_arg(current, data, 1, NO_NEED);
	arg[1] = get_arg(current, data, 2, SMALL_DIR | IND);
	arg[2] = get_arg(current, data, 3, SMALL_DIR);
	flag = GET;
	reg_value = set_reg_value(current, arg[0], NO_NEED, &flag);
	if (flag == BAD_REG)
		return (FAILURE);
	store_value(data, get_pos(current->position) + arg[1] + arg[2], reg_value);
	return (SUCCESS);
}
