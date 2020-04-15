/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_winner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:27:58 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 18:46:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t	core_present_winner(t_data *data)
{
	if (ft_printf("Contestant %hhu, \"%s\", has won !\n",
		data->champs[data->vm->last_alive_champ]->nb_player,
		data->champs[data->vm->last_alive_champ]->name) == FAILURE)
		return (core_error(8));
	return (SUCCESS);
}
