/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:18:10 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/07 15:26:29 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	get_arg_2_ind(t_carriages *current, t_data *data, int8_t arg_1)
{
	int32_t		arg_2_ind;

	arg_2_ind = core_get_ind(data,
			(current->position + current->to_jump) % MEM_SIZE);
	core_put_reg_ind(data, (current->position +
		(arg_2_ind % IDX_MOD) % MEM_SIZE), current->registres[arg_1 - 1]);
	current->to_jump += MEM_IND;
	return (SUCCESS);
}

static int8_t	get_arg_2_reg(t_carriages *current, t_data *data, int8_t arg_1)
{
	int8_t		arg_2_reg;

	arg_2_reg = core_get_reg(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (arg_2_reg == FAILURE)
		return (FAILURE);
	current->to_jump += MEM_REG;
	current->registres[arg_2_reg - 1] = arg_1;
	return (SUCCESS);
}

static int8_t	get_arg_1(t_carriages *current, t_data *data)
{
	int8_t		arg_1;

	arg_1 = core_get_reg(data,
		(current->position + current->to_jump) % MEM_SIZE);
	if (arg_1 == FAILURE)
		return (FALSE);
	current->to_jump += MEM_REG;
	return (arg_1);
}

int8_t			ope_st(t_carriages *current, t_data *data)
{
	uint8_t		ocp;
	int8_t		arg_1;

	current->to_jump = MEM_OP_CODE;
	ocp = core_get_ocp(data, (current->position + current->to_jump) % MEM_SIZE);
	current->to_jump += MEM_OCP;
	arg_1 = get_arg_1(current, data);
	if (arg_1 == FAILURE)
		return (FAILURE);
	if (ocp == REG_IND_)
		return (get_arg_2_ind(current, data, arg_1));
	else if (ocp == REG_REG_)
		return (get_arg_2_reg(current, data, arg_1));
	else
		return (FAILURE);
	return (SUCCESS);
}
