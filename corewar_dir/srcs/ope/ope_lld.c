/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_lld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:20:41 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/07 15:23:14 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int32_t	get_arg_1(t_carriages *current, t_data *data, uint8_t ocp)
{
	int32_t		arg_1;

	if (ocp == DIR_REG_)
	{
		arg_1 = core_get_dir(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_DIR;
	}
	else
	{
		arg_1 = core_get_ind(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_IND;
		arg_1 = core_ind_value_lld(data, (current->position % MEM_SIZE), arg_1);
	}
	return (arg_1);
}

int8_t			ope_lld(t_carriages *current, t_data *data)
{
	uint8_t		ocp;
	int32_t		arg_1;
	int8_t		arg_2;

	current->to_jump = MEM_OP_CODE;
	ocp = core_get_ocp(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (ocp != DIR_REG_ && ocp != IND_REG_)
		return (FAILURE);
	current->to_jump += MEM_OCP;
	arg_1 = get_arg_1(current, data, ocp);
	arg_2 = core_get_reg(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (arg_2 == FAILURE)
		return (FAILURE);
	current->to_jump += MEM_REG;
	current->registres[arg_2 - 1] = arg_1;
	current->carry = (arg_1 == 0) ? CARRY_ON : CARRY_OFF;
	return (SUCCESS);
}
