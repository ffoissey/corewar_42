/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:51:26 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/24 22:35:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_debug	*init_debug(void)
{
	static t_debug	debug;

	ft_bzero(&debug, sizeof(t_debug));
	ft_putendl_fd("\n - - - - - - - DEBUG MODE - - - - - - - ", STDERR_FILENO);
	return (&debug);	
}

void		print_debug_usage()
{
	ft_dprintf(STDERR_FILENO, "usage: use `help` for possible cmd\n");
}

int			get_cmd(t_vector *line, t_debug *debug)
{
	t_vector	*split;
	int			ret;

	ret = FAILURE;
	vct_split(NULL, NULL, INIT);
	split = vct_split(line, "\t ", NO_SEP);
	if (ft_strequ(vct_getstr(split), "goto") == TRUE
		|| ft_strequ(vct_getstr(split), "gt") == TRUE)
	{
		vct_del(&split);
		split = vct_split(line, "\t ", NO_SEP);
		if (vct_apply(split, IS_DIGIT) == TRUE)
		{
			debug->next_cycle = ft_atol(vct_getstr(split));
			debug->cmd = GOTO;
			ret = SUCCESS;
		}
		else
			ft_dprintf(STDERR_FILENO, "Bad arg: goto/gt [nb_cycle]\n");
	}
	else if (ft_strequ(vct_getstr(split), "print") == TRUE
			|| ft_strequ(vct_getstr(split), "p") == TRUE)
	{
		debug->cmd = PRINT;
		ret = SUCCESS;
	}
	else if (ft_strequ(vct_getstr(split), "info") == TRUE)
	{
		debug->cmd = INFO;
		ret = SUCCESS;
	}
	else if (ft_strequ(vct_getstr(split), "exit") == TRUE)
	{
		debug->cmd = EXIT;
		ret = SUCCESS;
	}
	else if (ft_strequ(vct_getstr(split), "help") == TRUE)
	{
		debug->cmd = HELP;
		ret = SUCCESS;
	}
	if (ret == FAILURE)
		print_debug_usage();
	vct_del(&split);
	return (ret);
}

void	read_cmd(t_debug *debug)
{
	t_vector	*line;

	line = vct_new(0);
	ft_putstr_fd("> ", STDERR_FILENO);
	while (vct_readline(line, STDIN_FILENO) > 0) // CATCH ERR READ
	{
		if (vct_len(line) > 0 && vct_apply(line, IS_SPACE) == FALSE)
		{
			if (get_cmd(line, debug) == SUCCESS)
				break ;
		}
		ft_putstr_fd("> ", STDERR_FILENO);
	}
	vct_del(&line);
}


void	process_cmd(t_data *data, t_debug *debug)
{
	if (debug->cmd == GOTO)
	{
		if (data->vm.nb_cycles == debug->next_cycle)
		{
			ft_dprintf(STDERR_FILENO, "You are at cycle %d\n",
				debug->next_cycle);
			debug->cmd = NO_CMD;
		}
		else if (data->vm.nb_cycles > debug->next_cycle)
		{
			ft_dprintf(STDERR_FILENO,
				"\033[31mCycle `%d' already past...\033[0m\nCur cycle: %d\033[0m\n"
				, debug->next_cycle, data->vm.nb_cycles);
			debug->cmd = NO_CMD;
		}
	}
	else if (debug->cmd == PRINT)
	{
		corewar_dump(data);
		debug->cmd = NO_CMD;
	}
	else if (debug->cmd == EXIT)
		data->debug = OFF;
	else if (debug->cmd == INFO)
	{
		ft_dprintf(STDERR_FILENO, "\n\n#################### INFORMATION ####################\n\n");
		ft_dprintf(STDERR_FILENO, "- number of players: %d\n", data->initialised_players);
		ft_dprintf(STDERR_FILENO, "- current cycle: %d\n", data->vm.nb_cycles);
		ft_dprintf(STDERR_FILENO, "- cycle to die: %d\n", data->vm.cycles_to_die);
		ft_dprintf(STDERR_FILENO, "\n- - - - - - - - - - -  CHAMPS - - - - - - - - - - - - -\n\n");
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (data->champs[i] == NULL)
				continue ;
			if (i != 0)
				ft_dprintf(STDERR_FILENO, "-------------------------------------------------------\n");
			ft_dprintf(STDERR_FILENO, "nb player\t\t=> %d\n", data->champs[i]->nb_player);
			ft_dprintf(STDERR_FILENO, "name\t\t\t=> %s\n", data->champs[i]->name);
			ft_dprintf(STDERR_FILENO, "comment\t\t\t=> %s\n", data->champs[i]->comment);
			ft_dprintf(STDERR_FILENO, "code size\t\t=> %d\n", data->champs[i]->exec_code_size);
			ft_dprintf(STDERR_FILENO, "last alive cycle\t=> %d\n", data->champs[i]->last_alive_cycle);
		}
		ft_dprintf(STDERR_FILENO, "\n- - - - - - - - - - - CARRIAGES - - - - - - - - - - - -\n\n");
		for (t_carriages *tmp = data->carriages; tmp != NULL; tmp = tmp->next)
		{
			if (tmp != data->carriages)
				ft_dprintf(STDERR_FILENO, "-------------------------------------------------------\n");
			ft_dprintf(STDERR_FILENO, "id\t\t=> %d\n", tmp->id);
			ft_dprintf(STDERR_FILENO, "last live cycle\t=> %d\n", tmp->last_live_cycle);
			ft_dprintf(STDERR_FILENO, "current pos\t=> 0x%.4x | %d\n", tmp->position, tmp->position);
			ft_dprintf(STDERR_FILENO, "carry\t\t=> %s\n", tmp->carry ? "ON" : "OFF");
			ft_dprintf(STDERR_FILENO, "registres: \n");
			for (int i = 0; i < REG_NUMBER; i++)
				ft_dprintf(STDERR_FILENO, "\treg %d: %d\n", i + 1, tmp->registres[i]);	
		}
		debug->cmd = NO_CMD;
	}
	else if (debug->cmd == HELP)
	{
		debug->cmd = NO_CMD;
		ft_dprintf(STDERR_FILENO, "CMD LIST:\n");
		ft_dprintf(STDERR_FILENO, "- help:\t\t\t ==> print cmd list\n");
		ft_dprintf(STDERR_FILENO, "- info:\t\t\t ==> print current info\n");
		ft_dprintf(STDERR_FILENO, "- goto/gt [nb_cycle]:\t ==> go to a cycle\n");
		ft_dprintf(STDERR_FILENO, "- print:\t\t ==> print current dump\n");
		ft_dprintf(STDERR_FILENO, "- exit:\t\t\t ==> exit debug mode\n");
	}
}

void	debug_process(t_data *data)
{
	static t_debug		*debug;

	if (data->debug == OFF || isatty(STDIN_FILENO) == FALSE)
		return ;
	if (debug == NULL)
		debug = init_debug();
	process_cmd(data, debug);
	while (debug->cmd == NO_CMD)
	{
		read_cmd(debug);
		process_cmd(data, debug);
	}
}
