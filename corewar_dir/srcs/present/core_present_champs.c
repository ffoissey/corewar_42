/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_champs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:11:39 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 17:42:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	core_print_champ_pres(t_data *data, const int8_t i)
{
	if (ft_putstr_fd("* Player ", STDOUT_FILENO) == FAILURE
		|| ft_putnbr_fd(i, STDOUT_FILENO) == FAILURE
		|| ft_putstr_fd(", weighing ", STDOUT_FILENO)
		== FAILURE
		|| ft_putnbr_fd(
		data->champs[i - 1]->exec_code_size,
		STDOUT_FILENO) == FAILURE
		|| ft_putstr_fd(" bytes, \"", STDOUT_FILENO)
		== FAILURE
		|| ft_putstr_fd(
		(char *)data->champs[i - 1]->name,
		STDOUT_FILENO) == FAILURE
		|| ft_putstr_fd("\" (\"", STDOUT_FILENO)
		== FAILURE
		|| ft_putstr_fd(
		(char *)data->champs[i - 1]->comment,
		STDOUT_FILENO) == FAILURE
		|| ft_putstr_fd("\") !\n", STDOUT_FILENO)
		== FAILURE)
		return (core_error(8));
	return (SUCCESS);
}

int8_t			core_present_champs(t_data *data)
{
	uint8_t i;

	i = 1;
	ft_putendl_fd("Introducing contestants...", STDOUT_FILENO);
	while (i <= 4)
	{
		if (data->champs[i - 1])
		{
			if (core_print_champ_pres(data, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
