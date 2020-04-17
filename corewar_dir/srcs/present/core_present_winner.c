/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_winner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:27:58 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/17 16:43:03 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t	core_present_winner(t_data *data)
{
	if (ft_printf("Contestant %hhu, \"%s\", has won !\n",
		data->champs[data->vm.last_alive_champ - 1]->nb_player,
		data->champs[data->vm.last_alive_champ - 1]->name) == FAILURE)
		return (core_error(8));
	return (SUCCESS);
}
