/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_process_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:30:39 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/27 11:43:21 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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

static void		msg_free_save_cmd(uint32_t cycle_diff, uint8_t is_free,
								int flag)
{
	if (flag == FREE_CMD)
	{
		if (is_free == TRUE)
			ft_dprintf(STDERR_FILENO, "\033[31mNo dump saved\n\033[0m");
		else
			ft_dprintf(STDERR_FILENO,
				"\033[32mDump [cycle %d] flushed\n\033[0m", cycle_diff);
	}
	else if (is_free == FALSE)
	{
		ft_dprintf(STDERR_FILENO,
		"\033[31mBe careful! A dump [cycle %d] is already saved.\n\033[0m",
			cycle_diff);
		ft_dprintf(STDERR_FILENO, "To save a new dump, first use `flush\n");
	}
}

static void		process_cmd_extend(t_data *data, t_debug *debug)
{
	static uint8_t	is_free = TRUE;
	static uint32_t	cycle_diff = 0;
	static uint32_t save_memory[MEM_SIZE];

	if (debug->cmd == SAVE)
	{
		msg_free_save_cmd(cycle_diff, is_free, SAVE_CMD);
		if (is_free == TRUE)
		{
			cycle_diff = debug->cur_cycle;
			ft_dprintf(STDERR_FILENO,
				"\033[32mDump [cycle %d] saved!\n\033[0m", cycle_diff);
			ft_memcpy(save_memory, data->vm.arena, sizeof(uint32_t) * MEM_SIZE);
			is_free = FALSE;
		}
	}
	else if (debug->cmd == FLUSH)
	{
		msg_free_save_cmd(cycle_diff, is_free, FREE_CMD);
		is_free = TRUE;
		cycle_diff = 0;
		ft_bzero(save_memory, sizeof(uint32_t) * MEM_SIZE);
	}
	else if (debug->cmd == DIFF)
		dump_diff(data, save_memory, is_free);
}

void			process_cmd(t_data *data, t_debug *debug)
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
	else if (debug->cmd == INFO || debug->cmd == HELP)
		debug->cmd == HELP ? debug_help() : debug_info(data);
	else if (debug->cmd == CLEAR)
		ft_dprintf(STDERR_FILENO, "\033[2J\033[H");
	process_cmd_extend(data, debug);
	debug->cmd = NO_CMD;
}
