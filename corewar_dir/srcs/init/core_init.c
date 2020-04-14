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

static int8_t		core_nb_player(t_champs *new_champ,
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

static int8_t		init_champ(int8_t nb_player, char *file_path, t_data *data)
{
	t_champs		*new_champ;

	new_champ = (t_champs *)ft_memalloc(sizeof(t_champs));
	if (new_champ == NULL)
		return (core_error(1));
	core_nb_player(new_champ, nb_player, data, file_path);
	return (SUCCESS);
}

static int8_t		check_n_args(int32_t count_arg, char **av, t_data *data)
{
	int8_t	nb_player;

	(void)(data);
	if (av[count_arg + 1] == NULL)
		return (core_error(2));
	if (ft_isanint(av[count_arg + 1]) == FALSE)
		return (core_error(2));
	nb_player = ft_atoi(av[count_arg + 1]);
	if ((nb_player > 0 && nb_player <= MAX_PLAYERS)
		&& (av[count_arg + 2] != NULL)
		&& (ft_strequ(av[count_arg + 2]
			+ ft_strlen(av[count_arg + 2]) - 4, ".cor") == TRUE))
		return (init_champ(nb_player, av[count_arg + 2], data));
	else
		return (core_error(2));
	data->initialised_players += 1;
	return (SUCCESS);
}

static int8_t		check_args(int32_t count_arg, char **av, t_data *data)
{
	if (ft_strequ(av[count_arg], "-n") == TRUE)
		return (check_n_args(count_arg, av, data));
	if (av[count_arg + 1] == NULL)
		return (core_error(9));
	if (ft_isanint(av[count_arg + 1]) == FALSE)
		return (core_error(9));
	data->dump = ft_atoi(av[count_arg + 1]);
	if (data->dump < 0)
		return (core_error(9));
	if ((av[count_arg + 2] != NULL)
		&& (ft_strequ(av[count_arg + 2]
			+ ft_strlen(av[count_arg + 2]) - 4, ".cor") == TRUE))
		return (init_champ(-1, av[count_arg + 2], data));
	else
		return (core_error(9));
	data->initialised_players += 1;
	return (SUCCESS);
}

int8_t				core_init_data(int32_t ac, char **av, t_data *data)
{
	int32_t		count_arg;

	data->initialised_players = 0;
	count_arg = 0;
	data->dump = OFF;
	while (++count_arg < ac && data->initialised_players <= MAX_PLAYERS)
	{
		if (ft_strequ(av[count_arg], "-n") == TRUE ||
			ft_strequ(av[count_arg], "-dump") == TRUE)
		{
			if (check_args(count_arg, av, data) == FAILURE)
				return (FAILURE);
			count_arg += 2;
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
