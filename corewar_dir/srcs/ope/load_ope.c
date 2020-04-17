/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:01 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 13:12:00 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	load_value(t_carriages *current, t_data *data, uint16_t flag)
{
	int32_t		arg[2];
	int16_t		reg_val;
	uint8_t		flag_reg;

	current->carry = CARRY_OFF;
	arg[0] = get_arg(current, data, 1, flag | IND);
	arg[1] = get_arg(current, data, 2, NO_NEED);
	flag = SET | GET;
	reg_val = set_reg_value(current, arg[1], arg[0], &flag_reg);
	if (flag_reg != BAD_REG && reg_val == 0)
		current->carry = CARRY_ON;
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}

static int8_t	load_indvalue(t_carriages *current, t_data *data, uint16_t flag)
{
	int32_t		arg[3];
	uint8_t		flag_reg;
	int16_t		pos;
	int16_t		to_load;

	arg[0] = get_arg(current, data, 1, SMALL_DIR | flag);
	arg[1] = get_arg(current, data, 2, SMALL_DIR);
	arg[2] = get_arg(current, data, 3, NO_NEED);
	pos = get_pos(arg[0] + arg[1]);
	if (flag == IND)
		pos %= IDX_MOD;
	to_load = get_ind_value(data, current->position, pos, IND);
	flag_reg = SET;
	set_reg_value(current, arg[2], to_load, &flag_reg);
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}

/*
**** LD 0x02
*/

int8_t			ope_ld(t_carriages *current, t_data *data)
{
	return (load_value(current, data, SMALL_DIR));
}

/*
**** LLD 0x0d
*/

int8_t			ope_lld(t_carriages *current, t_data *data)
{
	return (load_value(current, data, BIG_DIR));
}

/*
**** LDI 0x0a
*/

int8_t			ope_ldi(t_carriages *current, t_data *data)
{
	return (load_indvalue(current, data, IND));
}

/*
**** LLDI 0x0e
*/

int8_t			ope_lldi(t_carriages *current, t_data *data)
{
	return (load_indvalue(current, data, IND_LLD));
}
