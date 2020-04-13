/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:19:12 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/12 10:55:56 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		ope_zjmp(t_carriages *current, t_data *data)
{
	short		arg;

	arg = core_get_small_dir(data,
		(current->position + MEM_OP_CODE) % MEM_SIZE);
	if (current->carry == CARRY_ON)
		current->to_jump = arg % IDX_MOD;
	else
	{
		current->to_jump = MEM_OP_CODE;
		current->to_jump += MEM_SMALL_DIR;
	}
	return (SUCCESS);
}
