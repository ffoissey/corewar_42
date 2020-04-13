/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_attribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 13:35:13 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 17:21:48 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_lab_val(t_list *label_list, char *str, long *value)
{
	t_token	*label;

	while (label_list != NULL)
	{
		label = (t_token *)(label_list->content);
		if (ft_strequ(str, label->str) == TRUE)
		{
			*value = label->mem_offset;
			return (SUCCESS);
		}
		label_list = label_list->next;
	}
	return (FAILURE);
}

void		label_attribution(t_asm *env_asm)
{
	t_list	*token_list;
	t_token	*token;
	long	value;

	token_list = env_asm->token_list;
	while (token_list != NULL)
	{
		token = (t_token *)(token_list->content);
		if (token->type == DIRECT_LABEL || token->type == INDIRECT_LABEL)
		{
			value = 0;
			if (get_lab_val(env_asm->label_list, token->str, &value) == FAILURE)
				exit_error(UNKNOW_LABEL, token);
			token->value = (int32_t)(value - token->mem_offset);
		}
		token_list = token_list->next;
	}
}
