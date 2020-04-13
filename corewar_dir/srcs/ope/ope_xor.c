/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:22:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/06 12:47:22 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void		get_arg_1(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	int32_t		to_jump;

	args[3] = SUCCESS;
	to_jump = current->to_jump;
	if (ocp == REG_REG_REG_ || ocp == REG_DIR_REG_ || ocp == REG_IND_REG_)
	{
		args[0] = core_get_reg(data, (current->position + to_jump) % MEM_SIZE);
		if (args[0] == FAILURE)
			args[3] = FAILURE;
		args[0] = current->registres[args[0] - 1];
		current->to_jump += MEM_REG;
	}
	else if (ocp == DIR_REG_REG_ || ocp == DIR_DIR_REG_ || ocp == DIR_IND_REG_)
	{
		args[0] = core_get_dir(data, (current->position + to_jump) % MEM_SIZE);
		current->to_jump += MEM_DIR;
	}
	else if (ocp == IND_REG_REG_ || ocp == IND_DIR_REG_ || ocp == IND_IND_REG_)
	{
		args[0] = core_get_ind(data, (current->position + to_jump) % MEM_SIZE);
		args[0] = core_ind_value(data, current->position % MEM_SIZE, args[0]);
		current->to_jump += MEM_IND;
	}
	return ;
}

static void		get_arg_2(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	int32_t		to_jump;

	to_jump = current->to_jump;
	if (ocp == REG_DIR_REG_ || ocp == DIR_DIR_REG_ || ocp == IND_DIR_REG_)
	{
		args[1] = core_get_dir(data, (current->position + to_jump) % MEM_SIZE);
		current->to_jump += MEM_DIR;
	}
	else if (ocp == REG_REG_REG_ || ocp == DIR_REG_REG_ || ocp == IND_REG_REG_)
	{
		args[1] = core_get_reg(data, (current->position + to_jump) % MEM_SIZE);
		if (args[1] == FAILURE)
			args[3] = FAILURE;
		args[1] = current->registres[args[1] - 1];
		current->to_jump += MEM_REG;
	}
	else if (ocp == IND_IND_REG_ || ocp == DIR_IND_REG_ || ocp == REG_IND_REG_)
	{
		args[1] = core_get_ind(data, (current->position + to_jump) % MEM_SIZE);
		args[1] = core_ind_value(data, current->position % MEM_SIZE, args[1]);
		current->to_jump = MEM_IND;
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
		current->to_jump += MEM_REG;
		if (arg_3 == FAILURE)
			args[3] = FAILURE;
		args[2] = arg_3;
	}
	else
		args[3] = FAILURE;
	return ;
}

int8_t			ope_xor(t_carriages *current, t_data *data)
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
	current->registres[args[2] - 1] = args[0] ^ args[1];
	current->carry =
		(current->registres[args[2] - 1] == 0) ? CARRY_ON : CARRY_OFF;
	free(args);
	return (SUCCESS);
}
