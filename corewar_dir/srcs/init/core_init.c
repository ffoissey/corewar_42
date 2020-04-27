/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:25:50 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/27 14:16:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_champs	*init_champ(const char *file_path, const uint8_t nb_player)
{
	t_champs		*new_champ;

	new_champ = (t_champs *)ft_memalloc(sizeof(t_champs));
	if (new_champ == NULL)
		core_error(get_env_data(DATA), ER_MALLOC);
	new_champ->nb_player = nb_player;
	new_champ->file_path = file_path;
	return (new_champ);
}

static void		is_valid_player_name(const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len <= 4 || ft_strequ(name + (len - 4), ".cor") == FALSE)
		core_error(get_env_data(DATA), ER_FILE);
}

static void		get_next_player(t_data *data, const char *file_path,
							uint8_t nb_player)
{
	is_valid_player_name(file_path);
	if (data->initialised_players >= MAX_PLAYERS)
		core_error(data, ER_FILE);
	if (nb_player != NATURAL_ORDER && data->champs[--nb_player] != NULL)
		nb_player = NATURAL_ORDER;
	if (nb_player == NATURAL_ORDER)
	{
		while (nb_player < MAX_PLAYERS && data->champs[nb_player] != NULL)
			nb_player++;
	}
	data->champs[nb_player] = init_champ(file_path, (uint8_t)(nb_player + 1));
	data->initialised_players++;
}

t_data			*get_env_data(t_data *init)
{
	static t_data	*data;

	if (data == NULL)
		data = init;
	return (data);
}

void			core_init_data(const int32_t ac, const char **av, t_data *data)
{
	uint32_t	i;
	uint8_t		nb_player;

	ft_bzero(data, sizeof(t_data));
	get_env_data(data);
	i = core_init_flag(ac + 1, av, data);
	while (i < (uint32_t)ac)
	{
		nb_player = get_player_number(av, &i);
		get_next_player(data, av[i], nb_player);
		i++;
	}
}
