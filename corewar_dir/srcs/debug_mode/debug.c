/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:51:26 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/27 11:44:46 by ffoissey         ###   ########.fr       */
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

void			dump_diff(t_data *data, uint32_t *save_memory, uint8_t is_free)
{
	uint16_t	i;

	i = 0;
	
	if (is_free == TRUE)
	{
		ft_dprintf(STDERR_FILENO,
			"\033[31mNo dump saved\n\033[0muse `save' to save a dump\n");
		return ;
	}
	while (i < MEM_SIZE)
	{
		if (i % ONE_LINE == SUCCESS)
			ft_dprintf(STDERR_FILENO, "0x%04x : ", i);
		if (data->vm.arena[i] != save_memory[i])
			ft_dprintf(STDERR_FILENO, "\033[1;32m%02x \033[0m",
				(uint8_t)save_memory[i]);
		else
			ft_dprintf(STDERR_FILENO, "%02x ", (uint8_t)save_memory[i]);
		if (i > 0 && ((i + 1) % ONE_LINE == SUCCESS))
			ft_putchar_fd('\n', STDERR_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
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
