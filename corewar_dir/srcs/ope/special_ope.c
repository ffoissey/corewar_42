/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_ope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:10:11 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 19:15:12 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
**** LIVE 0x01
*/

static int		print_live(t_data *data, int32_t arg)
{
	if (ft_printf("Un processus dit que le joueur %d (%s) est en vie.\n",
			arg, data->champs[arg - 1]->name) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ope_live(t_carriages *current, t_data *data)
{
	int32_t		arg;
	enum e_type	type;

	data->vm.nb_lives += 1;
	current->last_live_cycle = data->vm.nb_cycles;
	type = OP_LIVE;
	arg = get_arg(current, data,
			INIT_ARG | BIG_DIR | NO_OCP | DIR_FLAG, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg = -arg;
	if (arg > 0 && arg <= MAX_PLAYERS
		&& data->champs[arg - 1] != NULL)
	{
		data->champs[arg - 1]->last_alive_cycle = data->vm.nb_cycles;
		data->vm.last_alive_champ = (uint8_t)arg;
		if (data->aff == ON)
			return (print_live(data, arg));
	}
	return (SUCCESS);
}

/*
**** AFF 0x10
*/

static int8_t	print_aff(t_carriages *current, int8_t arg_1)
{
	uint8_t	flag_reg;
	uint8_t	value;

	flag_reg = GET;
	value = set_reg_value(current, arg_1, NO_NEED, &flag_reg);
	if (flag_reg == BAD_REG)
		return (FAILURE);
	if (ft_printf("Aff : %c\n", value) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ope_aff(t_carriages *current, t_data *data)
{
	int8_t	arg_1;
	enum e_type	type;

	type = OP_AFF;
	arg_1 = get_arg(current, data, REG_NUM | INIT_ARG | REG_FLAG, &type);
	if (type == NO_OP)
		return (FAILURE);
	if (data->aff == ON)
		return (print_aff(current, arg_1));
	return (SUCCESS);
}

/*
**** ZJMP 0x09
*/

int8_t			ope_zjmp(t_carriages *current, t_data *data)
{
	int32_t		arg;
	enum e_type	type;

	type = OP_ZJMP;
	arg = get_arg(current, data,
			INIT_ARG | NO_OCP | SMALL_DIR | DIR_FLAG, &type);
	if (type == NO_OP)
		return (FAILURE);
	if (current->carry == CARRY_ON)
		current->to_jump = arg % IDX_MOD;
	return (SUCCESS);
}
