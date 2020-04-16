/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:14:42 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:15:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
