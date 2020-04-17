/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_ope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:16:25 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 12:12:17 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
**** ST 0x03
*/

int8_t			ope_st(t_carriages *current, t_data *data)
{
	int32_t		arg[2];
	uint8_t		ocp;
	int16_t		reg_value;
	uint8_t		flag;

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
	core_put_reg_ind(data, get_pos(current->position + arg[1]) % IDX_MOD, reg_value);
	return (SUCCESS);
}

/*
**** STI 0x0b
*/

int8_t			ope_sti(t_carriages *current, t_data *data)
{
	int32_t		args[3];

	args[0] = get_arg(current, data, 1, NO_NEED);
	args[1] = get_arg(current, data, 2, SMALL_DIR | IND);
	args[2] = get_arg(current, data, 3, SMALL_DIR);
	if (args[0] > 0 && args[0] <= REG_NUMBER)
		core_put_reg_ind(data, get_pos((current->position +
			args[1] + args[2]) % IDX_MOD), current->registres[args[0] - 1]);
	else
		return (FAILURE); //exit
	return (SUCCESS);
}
