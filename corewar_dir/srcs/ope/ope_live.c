/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:02:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 17:36:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	print_live(t_data *data, int32_t dir)
{
	ft_putstr_fd("Un processus dit que le joueur ", STDOUT_FILENO);
	ft_putnbr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("(", STDOUT_FILENO);
	ft_putstr_fd(data->champs[dir]->name, STDOUT_FILENO);
	ft_putstr_fd(") est en vie.\n", STDOUT_FILENO);
}

int8_t		ope_live(t_carriages *current, t_data *data)
{
	int32_t		dir;

	current->to_jump = MEM_OP_CODE;
	data->vm->nb_lives += 1;
	current->last_live_cycle = data->vm->nb_cycles;
	dir = core_get_dir(data, (current->position + current->to_jump) % MEM_SIZE);
	current->to_jump += MEM_DIR;
	dir = dir + 1;
	dir = -dir;
	if (dir >= 0 && dir < data->initialised_players
		&& data->champs[dir] != NULL)
	{
		data->champs[dir]->last_alive_cycle = data->vm->nb_cycles;
		data->vm->last_alive_champ = (uint8_t)dir;
		if (data->aff == ON)
			print_live(data, dir);
		return (SUCCESS);
	}
	return (SUCCESS);
}
