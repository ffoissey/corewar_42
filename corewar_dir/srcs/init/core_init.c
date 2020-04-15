/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:25:50 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 18:55:22 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			core_nb_player(t_champs *new_champ,
		int8_t nb_player, t_data *data, char *file_path)
{
	int8_t		count;

	count = -1;
	if (nb_player > 0 && data->champs[nb_player - 1] == NULL)
	{
		new_champ->nb_player = nb_player;
		new_champ->file_path = file_path;
		data->champs[nb_player - 1] = new_champ;
	}
	else
	{
		while (++count < 4)
		{
			if (data->champs[count] == NULL)
			{
				new_champ->nb_player = count + 1;
				new_champ->file_path = file_path;
				data->champs[count] = new_champ;
				break ;
			}
		}
	}
	return (SUCCESS);
}

int8_t			init_champ(int8_t nb_player, char *file_path, t_data *data)
{
	t_champs		*new_champ;

	new_champ = (t_champs *)ft_memalloc(sizeof(t_champs));
	if (new_champ == NULL)
		return (core_error(1));
	core_nb_player(new_champ, nb_player, data, file_path);
	return (SUCCESS);
}

int8_t			core_init_data(int32_t ac, char **av, t_data *data)
{
	int32_t		count_arg;

	data->initialised_players = 0;
	count_arg = 0;
	data->dump = OFF;
	while (++count_arg < ac && data->initialised_players <= MAX_PLAYERS)
	{
		if (ft_strequ(av[count_arg], "-n") == TRUE ||
			ft_strequ(av[count_arg], "-dump") == TRUE ||
			ft_strequ(av[count_arg], "-a") == TRUE)
		{
			if (core_init_flag(&count_arg, av, data) == FAILURE)
				return (FAILURE);
		}
		else if (ft_strequ(av[count_arg]
			+ ft_strlen(av[count_arg]) - 4, ".cor") == TRUE)
		{
			if (init_champ(-1, av[count_arg], data) == FAILURE)
				return (FAILURE);
			data->initialised_players += 1;
		}
		else
			return (core_error(0));
	}
	return (ac == count_arg ? SUCCESS : FAILURE);
}
