/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:14:01 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:21:19 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
