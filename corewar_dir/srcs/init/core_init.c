/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:25:50 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/17 13:45:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_champs		*init_champ(char *file_path, uint8_t nb_player)
{
	t_champs		*new_champ;

	new_champ = (t_champs *)ft_memalloc(sizeof(t_champs));
	if (new_champ != NULL)
	{
		new_champ->nb_player = nb_player;
		new_champ->file_path = file_path;
	}
	return (new_champ);
}

static uint8_t			is_valid_player_name(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len <= 4 || ft_strequ(name + (len - 4), ".cor") == FALSE)
		return (FALSE);
	return (TRUE);
}

static int8_t			get_next_player(t_data *data, char *file_path,
							int8_t nb_player)
{
	if (is_valid_player_name(file_path) == FALSE)
		return (core_error(0));
	if (data->initialised_players == MAX_PLAYERS)
		return (FAILURE);
	if (nb_player != NATURAL_ORDER && data->champs[--nb_player] != NULL)
		nb_player = NATURAL_ORDER;
	if (nb_player == NATURAL_ORDER)
	{
		while (nb_player < MAX_PLAYERS && data->champs[nb_player] != NULL)
			nb_player++;
	}
	data->champs[nb_player] = init_champ(file_path, nb_player + 1);
	if (data->champs[nb_player] == NULL)
		return (FAILURE);
	data->initialised_players++;
	return (SUCCESS);
}

static void			reorder_champs(t_champs **champs)
{
	uint8_t	i;

	i = 1;
	while (i < MAX_PLAYERS)
	{
		if (champs[i - 1] == NULL && champs[i] != NULL)
		{
			champs[i - 1] = champs[i];
			champs[i] = NULL;
			i = 0;
		}
		i++;
	}	
}

int8_t			core_init_data(int32_t ac, char **av, t_data *data)
{
	int32_t		i;
	int8_t		nb_player;

	ft_bzero(data, sizeof(t_data));
	i = core_init_flag(ac + 1, av, data);
	if (i == FAILURE)
		return (FAILURE);
	while (i < ac)
	{
		nb_player = get_player_number(av, &i);
		if (nb_player == FAILURE)
			return (FAILURE);
		if (get_next_player(data, av[i], nb_player) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (data->initialised_players < 2 || i != ac) 
		return (FAILURE);
	reorder_champs(data->champs);
	return (SUCCESS); 
}
