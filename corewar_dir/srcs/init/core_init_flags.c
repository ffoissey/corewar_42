/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:15:37 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/24 20:46:07 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int		ft_isanint(const char *str)
{
	long		nb;

	nb = ft_atol(str);
	return (nb <= INT_MAX && nb >= INT_MIN);
}

static int32_t	get_arg_number(const char *number_str)
{
	if (number_str == NULL || ft_isanint(number_str) == FALSE)
		core_error(get_env_data(DATA), ER_DUMP);
	return (ft_atoi(number_str));
}

uint8_t			get_player_number(const char **av, uint32_t *i)
{
	int32_t		nb_player;

	nb_player = NATURAL_ORDER;
	if (ft_strnequ(av[*i], "-n", 2) == TRUE)
	{
		if (ft_strequ(av[*i], "-n") == TRUE)
		{
			(*i)++;
			nb_player = get_arg_number(av[*i]);
		}
		else
			nb_player = get_arg_number(av[*i] + 2);
		if (nb_player <= 0 || nb_player > MAX_PLAYERS)
			core_error(get_env_data(DATA), ER_N_USAGE);
		(*i)++;
	}
	return ((uint8_t)nb_player);
}

uint32_t		core_init_flag(const int32_t ac, const char **av,
					t_data *data)
{
	uint32_t	i;

	i = 1;
	data->dump = OFF;
	data->aff = OFF;
	data->debug = OFF;
	while (i < (uint32_t)ac)
	{
		if (ft_strequ(av[i], "-debug") == TRUE)
			data->debug = ON;
		else if (ft_strequ(av[i], "-dump") == TRUE)
		{
			i++;
			data->dump = get_arg_number(av[i]);
			if (data->dump < 0)
				core_error(data, ER_DUMP);
		}
		else if (ft_strequ(av[i], "-a") == TRUE)
			data->aff = ON;
		else
			break ;
		i++;
	}
	return (i);
}
