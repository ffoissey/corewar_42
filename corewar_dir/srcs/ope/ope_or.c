/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:19:17 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 20:09:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			ope_or(t_carriages *current, t_data *data)
{
	int32_t		args[3];

	args[0] = get_arg(current, data, 1, NO_NEED);
	args[1] = get_arg(current, data, 2, NO_NEED);
	args[2] = get_arg(current, data, 3, NO_NEED);
	current->registres[args[2] - 1] = args[0] | args[1];
	current->carry =
		(current->registres[args[2] - 1] == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}
