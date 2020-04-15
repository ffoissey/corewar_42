/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:51:30 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 19:04:05 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	main_part2(t_data *data)
{
	if (core_init_carriages(data) == FAILURE)
	{
		core_free_all(data);
		return (FAILURE);
	}
	if (core_present_champs(data) == FAILURE)
		return (FAILURE);
	core_cycle(data);
	if (data->dump != DONE && core_present_winner(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int				main(int32_t ac, char **av)
{
	t_data		*data;

	if (ac < 2)
	{
		ft_putstr_fd(ERROR_MSG0, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data = (t_data *)ft_memalloc(sizeof(t_data));
	if (data == NULL)
	{
		ft_putstr_fd(ERROR_MSG1, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data->aff = OFF;
	if (core_init_data(ac, av, data) == FAILURE
		|| core_init_vm(data) == FAILURE)
	{
		core_free_all(data);
		return (EXIT_FAILURE);
	}
	if (core_read(data) == FAILURE || main_part2(data) == FAILURE)
		return (EXIT_FAILURE);
	core_free_all(data);
	return (EXIT_SUCCESS);
}
