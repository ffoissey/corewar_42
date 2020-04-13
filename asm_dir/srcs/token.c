/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:55:22 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 17:24:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_token	get_token(enum e_token type, t_vector *elem, t_asm *env_asm,
				const uint8_t flag)
{
	t_token token;

	token.initial_str = vct_dupstr(elem);
	if (type == LABEL)
		vct_cut(elem);
	else if (type == REG || type == INDIRECT_LABEL
		|| type == DIRECT || type == DIRECT_LABEL)
		vct_pop(elem);
	if (type == DIRECT_LABEL)
		vct_pop(elem);
	token.str = type == ENDL ? ft_strdup("\n") : vct_dupstr(elem);
	if (vct_getstr(elem) != NULL
		&& (token.initial_str == NULL || token.str == NULL))
		exit_error(MALLOC_ERROR, &token);
	token.type = type;
	token.mask = 0;
	token.op_size = 0;
	token.arg_size = 1;
	token.value = (type == REG || type == INDIRECT || type == DIRECT)
			? ft_atol(token.str) : 0;
	token.mem_offset = env_asm->mem_count;
	token.line = flag == DQUOTE ? env_asm->start_line_dquote : env_asm->line;
	token.col = flag == DQUOTE ? env_asm->start_col_dquote : env_asm->col;
	return (token);
}

static void		token_verification(t_vector *elem, t_token *token,
					t_asm *env_asm)
{
	if (token->type == UNKNOW)
		exit_error(UNKNOW_TOKEN, token);
	else if (is_label_type(token->type) == TRUE)
	{
		if (check_label(token->str) == FALSE)
			exit_error(WRONG_LABEL_NAME, token);
		if (token->type == LABEL &&
				is_label_uniq(env_asm->label_list, token->str) == FALSE)
			exit_error(DOUBLE_LABEL, token);
	}
	else if (is_num_type(token->type) && vct_apply(elem, IS_NUMBER) == FALSE)
		exit_error(NUMERIC_VALUE, token);
	else if (token->type == REG
			&& (token->value <= 0 || token->value > REG_NUMBER))
		exit_error(REG_VALUE, token);
}

int				extract_token(enum e_token type, t_vector *elem,
					t_asm *env_asm, const uint8_t flag)
{
	t_list	*token_node;
	t_token	token;

	if (type == STRING && flag != DQUOTE)
	{
		env_asm->start_line_dquote = env_asm->line;
		env_asm->start_col_dquote = env_asm->col;
		return (DQUOTE);
	}
	if (type == SPACE_TAB)
		type = SPACE;
	token = get_token(type, elem, env_asm, flag);
	token_verification(elem, &token, env_asm);
	token_node = ft_lstnew(&token, sizeof(token));
	ft_lstadd_back(type == LABEL ? &env_asm->label_list : &env_asm->token_list,
				token_node);
	env_asm->col += vct_len(elem);
	if (env_asm->op_ptr == NULL && type <= NB_OP)
		env_asm->op_ptr = token_node;
	else if (env_asm->op_ptr != NULL && type == ENDL)
		op_checker(env_asm);
	return (SUCCESS);
}
