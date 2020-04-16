/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:15:12 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 20:11:14 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
