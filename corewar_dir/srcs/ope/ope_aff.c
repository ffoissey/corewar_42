/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:15:37 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 18:34:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	print_aff(t_carriages *current, int8_t arg_1)
{
	if (ft_printf("Aff : %c\n", current->registres[arg_1 - 1] % 256) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ope_aff(t_carriages *current, t_data *data)
{
	int8_t	arg_1;
	uint8_t	ocp;

	current->to_jump = MEM_OP_CODE;
	ocp = core_get_ocp(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (ocp != REG_)
		return (FAILURE);
	current->to_jump += MEM_OCP;
	arg_1 = core_get_reg(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (arg_1 == FAILURE)
		return (FAILURE);
	current->to_jump += MEM_REG;
	if (data->aff == ON)
		return (print_aff(current, arg_1));
	return (SUCCESS);
}
