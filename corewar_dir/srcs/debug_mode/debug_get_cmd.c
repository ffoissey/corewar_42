/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_get_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 14:15:21 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/26 14:28:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int		get_goto_arg(t_debug *debug, t_vector *line)
{
	t_vector	*split;
	int			ret;
	long		nb;

	ret = SUCCESS;
	split = vct_split(line, "\t ", NO_SEP);
	if (vct_apply(split, IS_DIGIT) == TRUE)
	{
		nb = ft_atol(vct_getstr(split));
		if (nb > INT_MAX)
		{
			ft_dprintf(STDERR_FILENO,
					"goto: Nb_cycle must be between 0 and INT_MAX\n");
			ret = FAILURE;
		}
		else
			debug->next_cycle = (int)nb;
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "goto: Bad arg\nusage: goto [nb_cycle]\n");
		ret = FAILURE;
	}
	vct_del(&split);
	return (ret);
}

static int		get_cmd_extend(int i, t_debug *debug, int nb_debug,
					t_vector *line)
{
	int		ret;

	ret = SUCCESS;
	if (i == GOTO)
		ret = get_goto_arg(debug, line);
	else if (i == NEXT)
	{
		debug->next_cycle = debug->cur_cycle + 1;
		debug->cmd = GOTO;
	}
	else if (i > nb_debug)
	{
		ft_dprintf(STDERR_FILENO, "Bad cmd\n");
		ft_dprintf(STDERR_FILENO,
				"use `help' to display the available commands\n");
		ret = FAILURE;
	}
	if (ret == FAILURE)
		debug->cmd = NO_CMD;
	return (ret);
}

int				get_cmd(t_vector *line, t_debug *debug)
{
	t_vector	*split;
	int			nb_debug;
	const char	*str_debug[] = {"goto", "print", "info", "help", "exit", "next",
								"opinfo"};
	int			i;

	vct_split(NULL, NULL, INIT);
	i = 0;
	nb_debug = sizeof(str_debug) / sizeof(char *);
	split = vct_split(line, "\t ", NO_SEP);
	while (i < nb_debug)
	{
		if (ft_strequ(vct_getstr(split), str_debug[i]) == TRUE)
		{
			debug->cmd = i + 1;
			break ;
		}
		i++;
	}
	vct_del(&split);
	return (get_cmd_extend(i + 1, debug, nb_debug, line));
}

static void		print_prompt(t_debug *debug)
{
	ft_dprintf(STDERR_FILENO, "DEBUG MODE [\033[32m%d\033[0m] > ",
								debug->cur_cycle);
}

void			read_cmd(t_debug *debug)
{
	t_vector	*line;

	line = vct_new(0);
	print_prompt(debug);
	while (vct_readline(line, STDIN_FILENO) > 0)
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
