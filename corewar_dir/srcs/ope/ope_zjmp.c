/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:19:12 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:06:16 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		ope_zjmp(t_carriages *current, t_data *data)
{
	int32_t		arg;

	arg = get_arg(current, data, 1, NO_OCP | SMALL_DIR | DIR_FLAG);
	if (current->carry == CARRY_ON)
		current->to_jump = arg % IDX_MOD;
	return (SUCCESS);
}
