/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:26:15 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/22 14:28:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void store_value(t_data *data, int16_t position, int32_t arg_1, int32_t reg_value)
{
	int16_t	pos;

	pos = get_pos((position + arg_1 % IDX_MOD));
	core_put_reg_ind(data, pos, reg_value);
}
/*
**** ST 0x03
*/

int8_t			ope_st(t_carriages *current, t_data *data)
{
	int32_t		arg[2];
	uint8_t		ocp;
	uint8_t		flag;
	enum e_type	type;

	type = OP_ST;
	ocp = core_get_ocp(data, current->position + 1);
	arg[0] = get_arg(current, data, START_ARG, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, END_ARG | IND_NUM | IND | REG_NUM, &type); 
	if (type == NO_OP)
		return (FAILURE);
	flag = SET;
	if (ocp == REG_REG_)
	{
		set_reg_value(current, arg[1], arg[0], &flag);
		if (flag == BAD_REG)
			return (FAILURE);
	}
	else if (ocp == REG_IND_)
		store_value(data, get_pos(current->position), arg[1], arg[0]);
	else
		return (FAILURE);
	return (SUCCESS);
}

/*
**** STI 0x0b
*/

int8_t			ope_sti(t_carriages *current, t_data *data)
{
	int32_t		arg[3];
	enum e_type	type;

	type = OP_STI;
	arg[0] = get_arg(current, data, START_ARG, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, SMALL_DIR, &type);
	arg[2] = get_arg(current, data, END_ARG | SMALL_DIR, &type);
	store_value(data, get_pos(current->position), arg[1] + arg[2], arg[0]);
	return (SUCCESS);
}
