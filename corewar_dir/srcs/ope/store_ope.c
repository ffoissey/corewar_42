/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:26:15 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/18 20:59:26 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void store_value(t_data *data, int16_t position, int32_t arg_1, int32_t reg_value)
{
	int16_t	pos;

	arg_1 = get_pos(arg_1 % IDX_MOD);
	pos = get_pos((position + arg_1));
//	if (pos < 0)
//		pos = 0;
	//// ICICICICICICI
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
	ocp = core_get_ocp(data, current->position + current->to_jump);
	arg[0] = get_arg(current, data, INIT_ARG, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, IND | REG_NUM, &type); // IND_NUM ? 
	if (type == NO_OP)
		return (FAILURE);
	flag = SET;
	if (ocp == REG_REG_)
	{
		set_reg_value(current, arg[1], arg[0], &flag);
		if (flag == BAD_REG)
			return (FAILURE);
	}
	else
		store_value(data, get_pos(current->position), arg[1], arg[0]);
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
	arg[0] = get_arg(current, data, INIT_ARG, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, SMALL_DIR, &type);
	arg[2] = get_arg(current, data, SMALL_DIR, &type);
//	ft_printf("arg[0] = %d, arg[1] = %d, arg[2] = %d , pos= %d\n", arg[0], arg[1], arg[2], current->position);
	store_value(data, get_pos(current->position), arg[1] + arg[2], arg[0]);
	return (SUCCESS);
}
