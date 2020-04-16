/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:16:23 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:21:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
