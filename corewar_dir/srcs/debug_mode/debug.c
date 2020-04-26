/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:51:26 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/26 12:14:47 by ffoissey         ###   ########.fr       */
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
	int			nb_debug;
	const char	*str_debug[] = {"goto", "print", "info", "help", "exit", "next",
								"opinfo"};
	int			ret;
	int			i;

	ret = FAILURE;
	vct_split(NULL, NULL, INIT);
	i = 0;
	nb_debug = sizeof(str_debug) / sizeof(char *);
	split = vct_split(line, "\t ", NO_SEP);
	while (i < nb_debug)
	{
		if (ft_strequ(vct_getstr(split), str_debug[i]) == TRUE)
		{
			debug->cmd = i + 1;
			ret = SUCCESS;
			break ;
		}
		i++;
	}
	vct_del(&split);
	if (i + 1 == GOTO)
	{
		split = vct_split(line, "\t ", NO_SEP);
		if (vct_apply(split, IS_DIGIT) == TRUE)
		{
			debug->next_cycle = ft_atol(vct_getstr(split));
			debug->cmd = GOTO;
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "Bad arg: goto [nb_cycle]\n");
			ret = FAILURE;
		}
	}
	else if (i + 1 == NEXT)
	{
		debug->next_cycle = debug->cur_cycle + 1;
		debug->cmd = GOTO;
	}
	else if (i == nb_debug)
			ft_dprintf(STDERR_FILENO, "Bad cmd\n");
	if (ret == FAILURE)
		print_debug_usage();
	vct_del(&split);
	return (ret);
}

void	print_prompt(t_debug *debug)
{
	ft_dprintf(STDERR_FILENO, "DEBUG MODE [\033[32m%d\033[0m] > ",
								debug->cur_cycle); 
}

void	read_cmd(t_debug *debug)
{
	t_vector	*line;

	line = vct_new(0);
	print_prompt(debug);
	while (vct_readline(line, STDIN_FILENO) > 0) // CATCH ERR READ
	{
		if (vct_len(line) > 0 && vct_apply(line, IS_SPACE) == FALSE)
		{
			if (get_cmd(line, debug) == SUCCESS)
				break ;
		}
		print_prompt(debug);
	}
	vct_del(&line);
}


void	process_cmd(t_data *data, t_debug *debug)
{
	if (debug->cmd == GOTO)
	{
		if (debug->cur_cycle == debug->next_cycle)
		{
			ft_dprintf(STDERR_FILENO, "You are at cycle %d\n",
				debug->next_cycle);
			debug->cmd = NO_CMD;
		}
		else if (debug->cur_cycle > debug->next_cycle)
		{
			ft_dprintf(STDERR_FILENO,
				"\033[31mCycle %d already past.\033[0m\nCur cycle: %d\033[0m\n"
				, debug->next_cycle, debug->cur_cycle);
			debug->cmd = NO_CMD;
		}
		return ;
	}
	else if (debug->cmd == OPINFO)
		debug_opinfo();
	else if (debug->cmd == PRINT)
		corewar_dump(data);
	else if (debug->cmd == EXIT)
	{
		data->debug = OFF;
		return ;
	}
	else if (debug->cmd == INFO)
		debug_info(data);
	else if (debug->cmd == HELP)
	{
		ft_dprintf(STDERR_FILENO, "CMD LIST:\n");
		ft_dprintf(STDERR_FILENO, "- help:\t\t\t ==> print cmd list\n");
		ft_dprintf(STDERR_FILENO, "- info:\t\t\t ==> print current info\n");
		ft_dprintf(STDERR_FILENO, "- goto [nb_cycle]:\t ==> go to a cycle\n");
		ft_dprintf(STDERR_FILENO, "- print:\t\t ==> print current dump\n");
		ft_dprintf(STDERR_FILENO, "- exit:\t\t\t ==> exit debug mode\n");
		ft_dprintf(STDERR_FILENO, "- next:\t\t\t ==> go to next cycle\n");
		ft_dprintf(STDERR_FILENO, "- opinfo:\t\t ==> print info about op\n");
	}
	debug->cmd = NO_CMD;
}

void	debug_process(t_data *data)
{
	static t_debug		*debug;

	if (data->debug == OFF || isatty(STDIN_FILENO) == FALSE)
		return ;
	if (debug == NULL)
		debug = init_debug();
	debug->cur_cycle = data->vm.nb_cycles;
	process_cmd(data, debug);
	while (debug->cmd == NO_CMD)
	{
		read_cmd(debug);
		process_cmd(data, debug);
	}
}
