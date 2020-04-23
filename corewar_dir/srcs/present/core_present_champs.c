/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_champs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:11:39 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/22 16:25:35 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	core_print_champ_pres(t_data *data, const uint8_t i)
{
	if (ft_printf("* Player %hhu, weighing %zu bytes, \"%s\" (\"%s\") !\n",
		data->champs[i]->nb_player,
		data->champs[i]->exec_code_size,
		(char *)data->champs[i]->name,
		(char *)data->champs[i]->comment) == FAILURE)
		core_error(data, ER_STDCLOSED);
}

void		core_present_champs(t_data *data)
{
	uint8_t i;

	i = 0;
	if (ft_putendl("Introducing contestants...") == FAILURE)
		core_error(data, ER_STDCLOSED);
	while (i < MAX_PLAYERS)
	{
		if (data->champs[i] != NULL)
			core_print_champ_pres(data, i);
		i++;
	}
}
