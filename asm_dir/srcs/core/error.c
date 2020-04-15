/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:02:40 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/14 16:04:28 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_string_error(size_t index)
{
	static char *str_err[] = {ERR_NO_FILE_NAME, ERR_BAD_EXTENSION,
							ERR_BAD_FD, ERR_WRONG_LABEL_NAME, ERR_DOUBLE_LABEL,
							ERR_NUMERIC_VALUE, ERR_REG_VALUE, ERR_UNKNOW_TOKEN,
							ERR_BAD_TOKEN, ERR_BAD_ARG_OP, ERR_UNCLOSED_DQUOTE,
							ERR_NAME_TOO_LONG, ERR_COMMENT_TOO_LONG,
							ERR_DOUBLE_NAME, ERR_DOUBLE_COMMENT, ERR_MISS_NAME,
							ERR_MISS_COMMENT, ERR_BAD_PLACE_NAME,
							ERR_BAD_PLACE_COMMENT, ERR_UNKNOW_LABEL, ERR_NO_OPE,
							ERR_BAD_NB_ARG, ERR_TOO_BIG_NBR, ERR_WRITE,
							ERR_READ, ERR_OPEN, ERR_MALLOC, NULL};

	return (str_err[index]);
}

int			print_error(uint64_t err, t_token *token)
{
	char		*str_error;
	size_t		i;

	i = 0;
	while ((str_error = get_string_error(i)) != NULL)
	{
		if (err & (1 << i))
		{
			ft_dprintf(STDERR_FILENO, "\033[31mERROR: \033[0m%s", str_error);
			if (i > 22)
				ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			if (i <= 22 && token != NULL)
				ft_dprintf(STDERR_FILENO,
				"\t-> token: `%s' | line: %d | col: %d\n",
				token->initial_str, token->line, token->col);
			return (i + 2);
		}
		i++;
	}
	return (NO_ERR);
}

void		exit_usage(uint64_t err, char c)
{
	if (err == INVALID_OPT)
		ft_dprintf(STDERR_FILENO, "%s'%c'\n", ERR_INVALID_OPT, c);
	else if (err == TOO_MANY_ARG)
		ft_putendl_fd(ERR_TOO_MANY_ARG, STDERR_FILENO);
	ft_putendl_fd(USAGE, STDERR_FILENO);
	exit(EXIT_USAGE);
}
