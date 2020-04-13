/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:42:45 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 17:19:05 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_env(t_asm *env_asm)
{
	static char	*grammar[NB_TOKEN] = {"", LIVE, LD, ST, ADD, SUB,
						AND, OR, XOR, ZJMP,
						LDI, STI, FORK, LLD, LLDI, LFORK, AFF,
						NAME_CMD_STRING, COMMENT_CMD_STRING,
						"r", ":", "%", "%:", ",", "\t", " ", "\n",
						"#", ";", "\"",
						"label", "ind", "UNKNOW"};

	ft_bzero(env_asm, sizeof(t_asm));
	env_asm->grammar = grammar;
	env_asm->dquote = vct_new(DFL_VCT_SIZE);
	if (env_asm->dquote == NULL)
		exit_error(MALLOC_ERROR, NULL);
	get_env_asm(env_asm);
}

t_asm	*get_env_asm(t_asm *env_asm)
{
	static t_asm *keep_env;

	if (keep_env == NULL && env_asm != NULL)
		keep_env = env_asm;
	return (keep_env);
}

int		main(int ac, char **av)
{
	t_asm		env_asm;

	if (ac == 1)
	{
		print_usage();
		return (EXIT_USAGE);
	}
	init_env(&env_asm);
	get_file_fd(&env_asm, av[ac - 1]);
	parser(&env_asm);
	env_asm.output = encoding(&env_asm);
	if (env_asm.output == NULL)
		exit_error(MALLOC_ERROR, NULL);
	write_file(env_asm.output, av[ac - 1]);
	exit_routine();
	return (SUCCESS);
}
