/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_champs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:11:39 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 17:46:10 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	core_print_champ_pres(t_data *data, const int8_t i)
{
	if (ft_printf("* Player %hhu, weighing %zu, \"%s\" (\"%s\") !\n",
		data->champs[i]->nb_player,
		data->champs[i]->exec_code_size, 
		(char *)data->champs[i]->name,
		(char *)data->champs[i]->comment) == FAILURE)
		return (core_error(8));
	return (SUCCESS);
}

int8_t			core_present_champs(t_data *data)
{
	uint8_t i;

	i = 0;
	if (ft_putendl("Introducing contestants...") == FAILURE)
		return (FAILURE);
	while (i < MAX_PLAYERS) // CEST QUOI 4
	{
		if (data->champs[i] != NULL)
		{
			if (core_print_champ_pres(data, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
