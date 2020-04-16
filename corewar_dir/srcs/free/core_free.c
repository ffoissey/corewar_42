/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:43:44 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 17:46:48 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void		core_free_champ(t_data *data)
{
	uint8_t champ_nb;

	champ_nb = 0;
	while (champ_nb < MAX_PLAYERS)
	{
		free(data->champs[champ_nb]);
		data->champs[champ_nb] = NULL;
		champ_nb++;
	}
}

static void		free_carriage(t_carriages *carriage)
{
	if (carriage != NULL)
	{
		free_carriage(carriage->next);
		free(carriage);
	}
}

void			core_free_all(t_data *data)
{
	core_free_champ(data);
	free_carriage(data->carriages);
	data->carriages = NULL;
	exit(0);
}
