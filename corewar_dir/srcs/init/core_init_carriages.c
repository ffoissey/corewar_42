/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_carriages.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:46:23 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:39:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t		core_init_champs_carriages(t_data *data, uint8_t champ_nb,
			t_carriages *carriage, t_carriages *last)
{
	if (data->champs[champ_nb])
	{
		if (!(carriage = (t_carriages *)ft_memalloc(sizeof(t_carriages))))
			return (FAILURE);
		if (last == NULL)
		{
			data->carriages = carriage;
			carriage->id = 0;
		}
		else
		{
			last->next = carriage;
			carriage->id = last->id + 1;
		}
		carriage->previous = last;
		carriage->position = data->champs[champ_nb]->copy_start;
		carriage->cycle_needed = -1;
		ft_bzero(carriage->registres, REG_NUMBER);
		carriage->registres[0] = -data->champs[champ_nb]->nb_player;
		carriage->carry = CARRY_OFF;
		last = carriage;
		data->vm.nb_carriages++;
		return (SUCCESS);
	}
	return (SUCCESS);
}

static int8_t		core_init_cycle(t_data *data, uint8_t champ_nb,
						t_carriages *carriage, t_carriages *last)
{
	while (--champ_nb >= 0 && champ_nb <= 3)
	{
		if (core_init_champs_carriages(data, champ_nb, carriage, last)
			== FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int8_t				core_init_carriages(t_data *data)
{
	uint8_t			champ_nb;
	t_carriages		*carriage;
	t_carriages		*last;

	champ_nb = 4;
	last = NULL;
	carriage = NULL;
	if (core_init_cycle(data, champ_nb, carriage, last) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
