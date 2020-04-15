/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:42:45 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/15 14:31:18 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm			*get_env_asm(t_asm *env_asm)
{
	static t_asm *keep_env;

	if (keep_env == NULL && env_asm != NULL)
		keep_env = env_asm;
	return (keep_env);
}

static uint8_t	get_option(char **av, const int ac)
{
	int		i;
	int		j;
	uint8_t	opt_a;

	i = 0;
	opt_a = FALSE;
	while (++i < ac - 1 && av[i][0] == '-')
	{
		j = 1;
		if (ft_strequ(av[i], "--") == TRUE)
		{
			i++;
			break ;
		}
		while (av[i][j] == 'a')
		{
			opt_a = TRUE;
			j++;
		}
		if (av[i][j] != '\0')
			exit_usage(INVALID_OPT, av[i][j]);
	}
	if (i != ac - 1)
		exit_usage(TOO_MANY_ARG, 0);
	return (opt_a);
}

static void		init_env(t_asm *env_asm, const int ac, char **av)
{
	static char	*grammar[NB_TOKEN] = {"", LIVE, LD, ST, ADD, SUB,
									AND, OR, XOR, ZJMP,
									LDI, STI, FORK, LLD, LLDI, LFORK, AFF,
									NAME_CMD_STRING, COMMENT_CMD_STRING,
									"r", ":", "%", "%:", ",", "\t", " ", "\n",
									"#", ";", "\"",
									"label", "ind", "UNKNOW"};

	ft_bzero(env_asm, sizeof(t_asm));
	env_asm->a_opt = get_option(av, ac);
	env_asm->grammar = grammar;
	env_asm->dquote = vct_new(DFL_VCT_SIZE);
	if (env_asm->dquote == NULL)
		exit_error(MALLOC_ERROR, NULL);
	get_env_asm(env_asm);
}

int				main(int ac, char **av)
{
	t_asm		env_asm;

	if (ac == 1)
		exit_usage(NO_ERR, 0);
	init_env(&env_asm, ac, av);
	get_file_fd(&env_asm, av[ac - 1]);
	parser(&env_asm);
	env_asm.output = encoding(&env_asm);
	if (env_asm.output == NULL)
		exit_error(MALLOC_ERROR, NULL);
	write_file(&env_asm, av[ac - 1]);
	exit_routine();
	return (SUCCESS);
}
