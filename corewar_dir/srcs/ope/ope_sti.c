/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:14:01 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:11:28 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void		get_arg_1(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	args[3] = SUCCESS;
	if (ocp == REG_REG_REG_ || ocp == REG_REG_DIR_ || ocp == REG_DIR_DIR_
		|| ocp == REG_IND_REG_ || ocp == REG_IND_DIR_ || ocp == REG_DIR_REG_)
	{
		args[0] = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_REG;
		if (args[0] == FAILURE)
			args[3] = FAILURE;
	}
	else
		args[3] = FAILURE;
}

static void		get_arg_2(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	if (ocp == REG_REG_DIR_ || ocp == REG_REG_REG_)
	{
		if ((args[1] = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE)) == FAILURE)
			args[3] = FAILURE;
		args[1] = current->registres[args[1] - 1];
		current->to_jump += MEM_REG;
	}
	else if (ocp == REG_DIR_DIR_ || ocp == REG_DIR_REG_)
	{
		args[1] = core_get_small_dir(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_SMALL_DIR;
	}
	else if (ocp == REG_IND_REG_ || ocp == REG_IND_DIR_)
	{
		args[1] = core_get_ind(data,
			(current->position + current->to_jump) % MEM_SIZE);
		args[1] = core_ind_value(data, current->position % MEM_SIZE, args[1]);
		current->to_jump += MEM_IND;
	}
}

static void		get_arg_3(t_carriages *current,
			t_data *data, uint8_t ocp, int32_t *args)
{
	if (ocp == REG_IND_DIR_ || ocp == REG_DIR_DIR_ || ocp == REG_REG_DIR_)
	{
		args[2] = core_get_small_dir(data,
			(current->position + current->to_jump) % MEM_SIZE);
		current->to_jump += MEM_SMALL_DIR;
	}
	else if (ocp == REG_REG_REG_ || ocp == REG_IND_REG_ || ocp == REG_DIR_REG_)
	{
		args[2] = core_get_reg(data,
			(current->position + current->to_jump) % MEM_SIZE);
		if (args[2] == FAILURE)
			args[3] = FAILURE;
		args[2] = current->registres[args[2] - 1];
		current->to_jump += MEM_REG;
	}
}

int8_t			ope_sti(t_carriages *current, t_data *data)
{
	uint8_t		ocp;
	int32_t		args[4];

	ft_bzero(&args, 4);
	current->to_jump = MEM_OP_CODE;
	ocp = core_get_ocp(data, (current->position + current->to_jump) % MEM_SIZE);
	current->to_jump += MEM_OCP;
	get_arg_1(current, data, ocp, args);
	get_arg_2(current, data, ocp, args);
	get_arg_3(current, data, ocp, args);
	if (args[3] == FAILURE)
		return (FAILURE);
	core_put_reg_ind(data, (current->position +
		((args[1] + args[2]) % IDX_MOD) % MEM_SIZE),
			current->registres[args[0] - 1]);
	return (SUCCESS);
}
