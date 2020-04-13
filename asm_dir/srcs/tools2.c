/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 13:32:45 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 16:19:23 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	reset_split(void)
{
	vct_split(NULL, NULL, INIT);
}

void	reset_col_and_increment_line(t_asm *env_asm)
{
	env_asm->col = 1;
	env_asm->line++;
}

int		is_comment(t_vector *split)
{
	char	first_char;

	first_char = vct_getfirstchar(split);
	return (first_char == COMMENT_CHAR || first_char == ALT_COMMENT_CHAR);
}

int		is_op_token(t_token *token)
{
	return (token->type >= 1 && token->type <= 16);
}

t_list	*go_to_next_op(t_list *lst)
{
	while (lst != NULL && is_op_token((t_token *)(lst->content)) == FALSE)
		lst = lst->next;
	return (lst);
}
