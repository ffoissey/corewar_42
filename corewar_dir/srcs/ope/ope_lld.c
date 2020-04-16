/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_lld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:20:41 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:11:21 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"


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
