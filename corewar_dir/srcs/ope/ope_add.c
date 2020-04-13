/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:15:12 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/07 11:56:18 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		ope_add(t_carriages *current, t_data *data)
{
	uint8_t		ocp;
	int32_t		args[3];
	int32_t		count;

	count = 0;
	current->to_jump = MEM_OP_CODE;
	ocp = core_get_ocp(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (ocp != REG_REG_REG_)
		return (FAILURE);
	current->to_jump += MEM_OCP;
	while (count < 3)
	{
		args[count] = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_REG;
		if (args[count] == FAILURE)
			return (FAILURE);
		count++;
	}
	current->registres[args[2] - 1] =
		current->registres[args[1] - 1] + current->registres[args[0] - 1];
	current->carry =
		(current->registres[args[2] - 1] == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}
