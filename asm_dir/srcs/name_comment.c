/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 13:28:18 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 17:22:35 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_str(t_list **token_list, const uint8_t flag)
{
	t_token	*token;
	char	*str;

	str = NULL;
	*token_list = (*token_list)->next;
	while (*token_list != NULL)
	{
		token = (t_token *)((*token_list)->content);
		if (token->type != SPACE)
		{
			if (str == NULL && token->type == STRING)
				str = token->str;
			else if (token->type == ENDL)
				break ;
			else
				exit_error(BAD_TOKEN, token);
		}
		*token_list = (*token_list)->next;
	}
	if (flag == GET_NAME && ft_strlen(str) > PROG_NAME_LENGTH)
		exit_error(NAME_TOO_LONG, NULL);
	else if (flag == GET_COM && ft_strlen(str) > PROG_COMMENT_LENGTH)
		exit_error(COMMENT_TOO_LONG, NULL);
	return (str);
}

static void	check_token_name_and_comment(t_list **token_list, t_token *token,
									t_asm *env_asm, int *code_start)
{
	if (token->type == CMD_NAME)
	{
		if (env_asm->name != NULL)
			exit_error(DOUBLE_NAME, token);
		else if (*code_start == TRUE)
			exit_error(BAD_PLACE_NAME, token);
		env_asm->name = ft_memalloc(PROG_NAME_LENGTH + 1);
		if (env_asm->name == NULL)
			exit_error(MALLOC_ERROR, token);
		ft_strcpy(env_asm->name, get_str(token_list, GET_NAME));
	}
	else if (token->type == CMD_COMMENT)
	{
		if (env_asm->comment != NULL)
			exit_error(DOUBLE_COMMENT, token);
		else if (*code_start == TRUE)
			exit_error(BAD_PLACE_COMMENT, token);
		env_asm->comment = ft_memalloc(PROG_COMMENT_LENGTH + 1);
		if (env_asm->comment == NULL)
			exit_error(MALLOC_ERROR, token);
		ft_strcpy(env_asm->comment, get_str(token_list, GET_COM));
	}
	else
		*code_start = TRUE;
}

static int	is_start_of_code(t_list *token_list)
{
	t_token	*token;

	token = (t_token *)(token_list->content);
	return (token->type != CMD_NAME && token->type != CMD_COMMENT
			&& token->type != SPACE && token->type != ENDL);
}

void		get_name_and_comment(t_asm *env_asm)
{
	t_list	*token_list;
	t_token	*token;
	t_list	*head;
	int		code_s;

	token_list = env_asm->token_list;
	head = NULL;
	code_s = FALSE;
	while (token_list != NULL)
	{
		token = (t_token *)(token_list->content);
		if (token->type != SPACE && token->type != ENDL)
			check_token_name_and_comment(&token_list, token, env_asm, &code_s);
		if (head == NULL && (code_s = is_start_of_code(token_list)) == TRUE)
			head = token_list;
		token_list = token_list->next;
	}
	ft_lstdeltil(&env_asm->token_list, head, del_token);
	if (env_asm->name == NULL)
		exit_error(MISS_NAME, NULL);
	else if (env_asm->comment == NULL)
		exit_error(MISS_COMMENT, NULL);
}
