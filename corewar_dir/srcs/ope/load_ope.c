/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:01 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 11:16:08 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
**** LD 0x02
*/

int8_t			ope_ld(t_carriages *current, t_data *data)
{
	int32_t		arg_1;
	int32_t		arg_2;

	arg_1 = get_arg(current, data, 1, SMALL_DIR | IND);
	arg_2 = get_arg(current, data, 2, NO_NEED);
	if (arg_2 <= 0 || arg_2 > REG_NUMBER)
		return (FAILURE); //exit
	current->registres[arg_2 - 1] = arg_1;
	current->carry = (arg_1 == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}

/*
**** LLD 0x0d
*/

int8_t			ope_lld(t_carriages *current, t_data *data)
{
	int32_t		arg_1;
	int8_t		arg_2;

	arg_1 = get_arg(current, data, 1, BIG_DIR | IND);
	arg_2 = get_arg(current, data, 2, NO_NEED);
	current->registres[arg_2 - 1] = arg_1;
	current->carry = (arg_1 == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}

/*
**** LDI 0x0a
*/

int8_t			ope_ldi(t_carriages *current, t_data *data)
{
	int32_t		args[3];

	args[0] = get_arg(current, data, 1, SMALL_DIR | IND);
	args[1] = get_arg(current, data, 2, SMALL_DIR);
	args[2] = get_arg(current, data, 3, NO_NEED);
	current->registres[args[2] - 1] = get_ind_value(data, current->position,
								get_pos((args[0] + args[1])) % IDX_MOD, IND);
	return (SUCCESS);
}

/*
**** LLDI 0x0e
*/

int8_t			ope_lldi(t_carriages *current, t_data *data)
{
	int32_t		args[3];

	args[0] = get_arg(current, data, 1, SMALL_DIR | IND_LLD);
	args[1] = get_arg(current, data, 2, SMALL_DIR);
	args[2] = get_arg(current, data, 3, NO_NEED);
	current->registres[args[2] - 1] =
		get_ind_value(data, current->position, args[0] + args[1], IND);
	return (SUCCESS);
}
