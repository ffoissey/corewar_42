/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:14:42 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/07 15:23:59 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void		get_arg_1(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	args[3] = SUCCESS;
	if (ocp == REG_REG_REG_ || ocp == REG_DIR_REG_ || ocp == REG_IND_REG_)
	{
		if ((args[0] = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE)) == FAILURE)
			args[3] = FAILURE;
		args[0] = current->registres[args[0] - 1];
		current->to_jump += MEM_REG;
	}
	else if (ocp == DIR_REG_REG_ || ocp == DIR_DIR_REG_ || ocp == DIR_IND_REG_)
	{
		args[0] = core_get_small_dir(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_SMALL_DIR;
	}
	else if (ocp == IND_REG_REG_ || ocp == IND_DIR_REG_ || ocp == IND_IND_REG_)
	{
		args[0] = core_get_ind(data,
			(current->position + current->to_jump) % MEM_SIZE);
		args[0] = core_ind_value(data, current->position % MEM_SIZE, args[0]);
		current->to_jump += MEM_IND;
	}
	return ;
}

static void		get_arg_2(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	if (ocp == REG_DIR_REG_ || ocp == DIR_DIR_REG_ || ocp == IND_DIR_REG_)
	{
		args[1] = core_get_small_dir(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_SMALL_DIR;
	}
	else if (ocp == REG_REG_REG_ || ocp == DIR_REG_REG_ || ocp == IND_REG_REG_)
	{
		args[1] = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE);
		if (args[1] == FAILURE)
			args[3] = FAILURE;
		args[1] = current->registres[args[1] - 1];
		current->to_jump += MEM_REG;
	}
	return ;
}

static void		get_arg_3(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	int8_t		arg_3;

	if (ocp == REG_REG_REG_ || ocp == DIR_REG_REG_ || ocp == IND_REG_REG_
		|| ocp == REG_IND_REG_ || ocp == DIR_IND_REG_ || ocp == IND_IND_REG_
		|| ocp == REG_DIR_REG_ || ocp == IND_DIR_REG_ || ocp == DIR_DIR_REG_)
	{
		arg_3 = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE);
		if (arg_3 == FAILURE)
			args[3] = FAILURE;
		args[2] = (int32_t)arg_3;
		current->to_jump += MEM_REG;
	}
	else
		args[3] = FAILURE;
	return ;
}

int8_t			ope_lldi(t_carriages *current, t_data *data)
{
	uint8_t		ocp;
	int32_t		*args;

	args = (int32_t *)ft_memalloc(sizeof(int32_t) * 4);
	if (args == NULL)
		return (FAILURE);
	current->to_jump = MEM_OP_CODE;
	ocp = core_get_ocp(data, (current->position + current->to_jump) % MEM_SIZE);
	current->to_jump += MEM_OCP;
	get_arg_1(current, data, ocp, args);
	get_arg_2(current, data, ocp, args);
	get_arg_3(current, data, ocp, args);
	if (args[3] == FAILURE)
	{
		free(args);
		return (FAILURE);
	}
	current->registres[args[2] - 1] =
		core_ind_value_lld(data, current->position, args[0] + args[1]);
	free(args);
	return (SUCCESS);
}
