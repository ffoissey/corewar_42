/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:51:26 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/26 19:30:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_debug	*init_debug(void)
{
	static t_debug	debug;
	uint8_t			i;
	const char		*debug_str[] = {"\n\n ______   _______  ______",
						"            _______ ",
						"   _______  _______  ______   _______ \n",
						"(  __  \\ (  ____ \\(  ___ \\ |\\     /|(  ____ \\",
						"  (       )(  ___  )(  __  \\ (  ____ \\ \n",
						"| (  \\  )| (    \\/| (   ) )| )   ( || (    \\/  ",
						"| () () || (   ) || (  \\  )| (    \\/ \n",
						"| |   ) || (__    | (__/ / | |   | || |      ",
						"  | || || || |   | || |   ) || (__     \n",
						"| |   | ||  __)   |  __ (  | |   | || | ____  ",
						" | |(_)| || |   | || |   | ||  __)    \n",
						"| |   ) || (      | (  \\ \\ | |   | || | \\_ ",
						" )  | |   | || |   | || |   ) || (       \n",
						"| (__/  )| (____/\\| )___) )| (___) || (___) | ",
						" | )   ( || (___) || (__/  )| (____/\\ \n",
						"(______/ (_______/(______/ (_______)(_______) ",
							" |/     \\|(_______)(______/ (_______/ \n\n\n\n"};

	ft_bzero(&debug, sizeof(t_debug));
	i = 0;
	while (i < 17)
		ft_dprintf(STDERR_FILENO, "\033[1;35m%s\033[0m", debug_str[i++]);
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
			"\033[31mCycle %d has already passed\033[0m\nCur cycle: %d\033[0m\n"
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
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		corewar_dump(data);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (debug->cmd == EXIT)
	{
		data->debug = OFF;
		return ;
	}
	else if (debug->cmd == INFO)
		debug_info(data);
	else if (debug->cmd == HELP)
		debug_help();
	else if (debug->cmd == CLEAR)
		ft_dprintf(STDERR_FILENO, "\033[2J\033[H");
	debug->cmd = NO_CMD;
}

void			debug_process(t_data *data)
{
	static t_debug		*debug;

	if (data->debug == OFF || isatty(STDIN_FILENO) == FALSE) //isatty interdit
		return ;
	if (debug == NULL)
		debug = init_debug();
	debug->cur_cycle = data->vm.nb_cycles;
	process_cmd(data, debug);
	while (debug->cmd == NO_CMD && data->debug != OFF)
	{
		read_cmd(data, debug);
		process_cmd(data, debug);
	}
}
