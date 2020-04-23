/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:51:30 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/22 15:38:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int				main(int32_t ac, char **av)
{
	t_data		data;

	if (ac < 2)
	{
		ft_putstr_fd(ERROR_MSG13, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	core_init_data(ac, av, &data);
	core_read(&data);
	core_init_carriages(&data);
	core_present_champs(&data);
	core_cycle(&data);
	core_present_winner(&data);
	core_free_all(&data, NO_ERROR);
	return (EXIT_SUCCESS);
}
