/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:51:26 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/26 14:29:29 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_debug	*init_debug(void)
{
	static t_debug	debug;

	ft_bzero(&debug, sizeof(t_debug));
	ft_putendl_fd("\n\n - - - - - - - DEBUG MODE - - - - - - - \n\n",
				STDERR_FILENO);
	return (&debug);
}

static void		debug_goto(t_debug *debug)
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
}

static void		process_cmd(t_data *data, t_debug *debug)
{
	if (debug->cmd == GOTO)
	{
		debug_goto(debug);
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
		debug_help();
	debug->cmd = NO_CMD;
}

void			debug_process(t_data *data)
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
