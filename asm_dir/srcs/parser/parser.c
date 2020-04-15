/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:06:56 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/15 14:53:17 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	find_token(t_vector *elem, t_asm *env_asm)
{
	enum e_token	type;
	size_t			len;

	type = NB_TRUE_TOKEN;
	if (vct_getlastchar(elem) == LABEL_CHAR)
		return (extract_token(LABEL, elem, env_asm, 0));
	while (--type > 0)
	{
		len = ft_strlen(env_asm->grammar[type]);
		if (type <= NB_KEYWORD_TOKEN)
		{
			if (ft_strequ(vct_getstr(elem), env_asm->grammar[type]) == TRUE)
				return (extract_token(type, elem, env_asm, 0));
		}
		else if (ft_strnequ(vct_getstr(elem), env_asm->grammar[type], len)
				== TRUE)
			return (extract_token(type, elem, env_asm, 0));
	}
	if (vct_apply(elem, IS_NUMBER) == TRUE)
		return (extract_token(INDIRECT, elem, env_asm, 0));
	return (extract_token(UNKNOW, elem, env_asm, 0));
}

static int	get_dquote(t_vector *line, t_asm *env_asm, const uint8_t flag)
{
	size_t			len_dquote;

	if (flag == ADD_ENDL)
	{
		if (vct_push(line, '\n') == FAILURE)
			exit_error(MALLOC_ERROR, NULL);
	}
	else if (flag == CUT_TIL_DQUOTE)
		vct_popfrom(line, (size_t)(vct_chr(line, '\"') + 1));
	len_dquote = vct_clen(line, '\"');
	if (vct_addnstr(env_asm->dquote, vct_getstr(line), len_dquote) == FAILURE)
		exit_error(MALLOC_ERROR, NULL);
	if (len_dquote != vct_len(line) && vct_chr(line, '\"') != FAILURE)
	{
		extract_token(STRING, env_asm->dquote, env_asm, DQUOTE);
		vct_popfrom(line, len_dquote + 1);
		vct_clear(env_asm->dquote);
		return (SUCCESS);
	}
	return (DQUOTE);
}

static int	split_loop(t_vector *line, t_asm *env_asm)
{
	t_vector		*split;
	int				ret;

	ret = SUCCESS;
	reset_split();
	while ((split = vct_split(line, DELIMITER_CHARS, EACH_SEP)) != NULL
			&& is_comment(split) == FALSE)
	{
		if ((ret = find_token(split, env_asm)) == FAILURE)
			break ;
		else if (ret == DQUOTE)
		{
			if ((ret = get_dquote(line, env_asm, CUT_TIL_DQUOTE)) == DQUOTE)
				break ;
			reset_split();
		}
		vct_del(&split);
	}
	vct_del(&split);
	return (ret);
}

void		parser(t_asm *env_asm)
{
	t_vector		*line;
	int				ret;
	int				ret_read;

	line = vct_new(DFL_VCT_SIZE);
	if (line == NULL)
		exit_error(MALLOC_ERROR, NULL);
	ret = SUCCESS;
	while ((ret_read = vct_readline(line, env_asm->fd)) > 0)
	{
		reset_col_and_increment_line(env_asm);
		if (ret == DQUOTE && get_dquote(line, env_asm, ADD_ENDL) == DQUOTE)
			continue ;
		if ((ret = split_loop(line, env_asm)) != DQUOTE)
			extract_token(ENDL, NULL, env_asm, 0);
	}
	vct_del(&line);
	if (ret_read == FAILURE)
		exit_error(READ_ERROR, NULL);
	if (ret == DQUOTE)
		exit_error(UNCLOSED_DQUOTE, NULL);
	get_name_and_comment(env_asm);
	label_attribution(env_asm);
	if (env_asm->mem_count == 0)
		exit_error(NO_OPE, NULL);
}
