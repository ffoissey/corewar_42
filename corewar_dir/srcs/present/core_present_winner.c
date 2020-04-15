/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_winner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:27:58 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 17:37:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t	core_present_winner(t_data *data)
{
	if (ft_putstr_fd("Contestant ", STDOUT_FILENO) == FAILURE
		|| ft_putnbr_fd(
		data->champs[data->vm->last_alive_champ]->nb_player,
		STDOUT_FILENO) == FAILURE
		|| ft_putstr_fd(", \"", STDOUT_FILENO) == FAILURE
		|| ft_putstr_fd(
		data->champs[data->vm->last_alive_champ]->name, STDOUT_FILENO)
		== FAILURE
		|| ft_putstr_fd("\", has won !\n", STDOUT_FILENO) == FAILURE)
		return (core_error(8));
	return (SUCCESS);
}
