/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:43:44 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 18:56:45 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void		core_free_champ(t_data *data)
{
	int8_t champ_nb;

	champ_nb = 0;
	while (champ_nb < 4)
	{
		if (data->champs[champ_nb])
		{
			free(data->champs[champ_nb]);
			data->champs[champ_nb] = NULL;
		}
		champ_nb++;
	}
}

void			core_free_all(t_data *data)
{
	t_carriages	*carriage;
	t_carriages	*next;

	if (data->vm)
	{
		free(data->vm);
		data->vm = NULL;
	}
	core_free_champ(data);
	carriage = data->carriages;
	while (carriage)
	{
		next = carriage->next;
		free(carriage);
		carriage = next;
	}
	free(data);
	return ;
}
