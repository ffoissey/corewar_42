/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_carriages.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:46:23 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/17 17:17:30 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void		core_init_champs_carriages(t_data *data, uint8_t champ_nb)
{
	t_carriages *carriage;

	errno = 0;
	carriage = (t_carriages *)ft_memalloc(sizeof(t_carriages));
	if (carriage == NULL)
		core_error(data, ER_MALLOC);
	ft_bzero(carriage->registres, REG_NUMBER);
	carriage->position = (uint16_t)data->champs[champ_nb]->copy_start;
	carriage->registres[0] = -data->champs[champ_nb]->nb_player;
	carriage->cycle_needed = -1;
	carriage->carry = CARRY_OFF;
	carriage->id = champ_nb;
	carriage->previous = NULL;
	carriage->next = data->carriages;
	if (data->carriages != NULL)
		data->carriages->previous = carriage;
	data->carriages = carriage;
	data->vm.nb_carriages++;
}

void				core_init_carriages(t_data *data)
{
	uint8_t			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (data->champs[i] != NULL)
			core_init_champs_carriages(data, i);
		i++;
	}
}
