/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_ope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:10:11 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 13:39:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
**** LIVE 0x01
*/

static int		print_live(t_data *data, int32_t arg)
{
	if (ft_printf("Un processus dit que le joueur %d (%s) est en vie.\n",
			arg, data->champs[arg]->name) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ope_live(t_carriages *current, t_data *data)
{
	int32_t		arg;

	data->vm.nb_lives += 1;
	current->last_live_cycle = data->vm.nb_cycles;
	arg = get_arg(current, data, INIT_ARG | BIG_DIR | NO_OCP | DIR_FLAG);
	arg = arg + 1;
	arg = -arg;
	if (arg >= 0 && arg < data->initialised_players
		&& data->champs[arg] != NULL)
	{
		data->champs[arg]->last_alive_cycle = data->vm.nb_cycles;
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
	if (ft_printf("Aff : %c\n", current->registres[arg_1 - 1] % 256) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ope_aff(t_carriages *current, t_data *data)
{
	int8_t	arg_1;

	arg_1 = get_arg(current, data, INIT_ARG | NO_OCP | REG_FLAG);
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

	arg = get_arg(current, data, INIT_ARG | NO_OCP | SMALL_DIR | DIR_FLAG);
	if (current->carry == CARRY_ON)
		current->to_jump = arg % IDX_MOD;
	return (SUCCESS);
}
