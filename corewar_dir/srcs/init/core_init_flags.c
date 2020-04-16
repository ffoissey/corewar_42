/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:15:37 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 17:24:25 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int32_t	get_arg_number(char *number_str)
{
	if (number_str == NULL || ft_isanint(number_str) == FALSE)
		return (core_error(9));
	return (ft_atoi(number_str));
}

int8_t			get_player_number(char **av, int32_t *i)
{
	int8_t		nb_player;

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
			return (core_error(2));
		(*i)++;
	}
	return (nb_player);
}

int32_t			core_init_flag(int32_t ac, char **av,
					t_data *data)
{
	int32_t	i;
	
	i = 1;
	data->dump = OFF;
	data->aff = OFF;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-dump") == TRUE)
		{
			i++;
			data->dump = get_arg_number(av[i]);
			if (data->dump < 0)
				return (FAILURE);
		}
		else if (ft_strequ(av[i], "-a") == TRUE)
			data->aff = ON;
		else
			break ;
		i++;
	}
	return (i);
}
