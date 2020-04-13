/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_present_champs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:11:39 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 18:46:44 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	core_print_champ_pres(t_data *data, int8_t i)
{
	if (ft_putstr_fd("* Player ", STDIN_FILENO) == FAILURE
		|| ft_putnbr_fd(i, STDIN_FILENO) == FAILURE
		|| ft_putstr_fd(", weighing ", STDIN_FILENO)
		== FAILURE
		|| ft_putnbr_fd(
		data->champs[i - 1]->exec_code_size,
		STDIN_FILENO) == FAILURE
		|| ft_putstr_fd(" bytes, \"", STDIN_FILENO)
		== FAILURE
		|| ft_putstr_fd(
		(char *)data->champs[i - 1]->name,
		STDIN_FILENO) == FAILURE
		|| ft_putstr_fd("\" \(\"", STDIN_FILENO)
		== FAILURE
		|| ft_putstr_fd(
		(char *)data->champs[i - 1]->comment,
		STDIN_FILENO) == FAILURE
		|| ft_putstr_fd("\") !\n", STDIN_FILENO)
		== FAILURE)
		return (core_error(8));
	return (SUCCESS);
}

int8_t			core_present_champs(t_data *data)
{
	int8_t i;

	i = 1;
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
