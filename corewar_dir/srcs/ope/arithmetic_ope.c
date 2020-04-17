/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_ope.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:19:45 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 11:20:49 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
*** ADD 0x04
*/

int8_t		ope_add(t_carriages *current, t_data *data)
{
	int32_t		args[3];
	int32_t		count;

	count = 0;
	current->to_jump = MEM_OP_CODE;
	while (count < 3)
	{
		args[count] = get_arg(current, data, count + 1, NO_NEED);
		count++;
	}
	current->registres[args[2] - 1] =
		current->registres[args[1] - 1] + current->registres[args[0] - 1];
	current->carry =
		(current->registres[args[2] - 1] == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}

/*
*** SUB 0x05
*/

int8_t		ope_sub(t_carriages *current, t_data *data)
{
	int32_t		args[3];
	int32_t		count;

	count = 0;
	current->to_jump = MEM_OP_CODE;
	while (count < 3)
	{
		args[count] = get_arg(current, data, count + 1, NO_NEED);
		count++;
	}
	current->registres[args[2] - 1] =
		current->registres[args[1] - 1] - current->registres[args[0] - 1];
	current->carry =
		(current->registres[args[2] - 1] == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}
