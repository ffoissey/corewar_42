#include "core.h"

static int8_t		check_n_args(int32_t count_arg, char **av, t_data *data)
{
	int8_t	nb_player;

	if (av[count_arg + 1] == NULL)
		return (core_error(2));
	if (ft_isanint(av[count_arg + 1]) == FALSE)
		return (core_error(2));
	nb_player = ft_atoi(av[count_arg + 1]);
	if ((nb_player > 0 && nb_player <= MAX_PLAYERS)
		&& (av[count_arg + 2] != NULL) && (ft_strequ(av[count_arg + 2]
		+ ft_strlen(av[count_arg + 2]) - 4, ".cor") == TRUE))
	{
		if (init_champ(nb_player, av[count_arg + 2], data) == SUCCESS)
		{
			data->initialised_players += 1;
			return (SUCCESS);
		}
		return (FAILURE);
	}
	else
		return (core_error(2));
	data->initialised_players += 1;
	return (SUCCESS);
}

static int8_t		check_dump_args(int32_t count_arg, char **av, t_data *data)
{
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
	{
		if (init_champ(-1, av[count_arg + 2], data) == SUCCESS)
		{
			data->initialised_players += 1;
			return (SUCCESS);
		}
		return (FAILURE);
	}
	else
		return (core_error(9));
	data->initialised_players += 1;
	return (SUCCESS);
}

int8_t		core_init_flag(int32_t *count_arg, char **av, t_data *data)
{
	if (ft_strequ(av[*count_arg], "-n") == TRUE)
	{
		if (check_n_args(*count_arg, av, data) == FAILURE)
			return (FAILURE);
		*count_arg += 2;
	}
	else if (ft_strequ(av[*count_arg], "-dump") == TRUE)
	{
		if (check_dump_args(*count_arg, av, data) == FAILURE)
			return (FAILURE);
		*count_arg += 2;
	}
	else if (ft_strequ(av[*count_arg], "-a") == TRUE)
	{
		data->aff = ON;
		if (av[*count_arg + 1] == NULL && data->initialised_players == 0)
			return (core_error(9));
	}
	return (SUCCESS);
}
