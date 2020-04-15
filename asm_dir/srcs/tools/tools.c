/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 21:04:00 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/15 14:37:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_arg_type(const enum e_token type)
{
	return (is_num_type(type) || type == INDIRECT_LABEL
		|| type == DIRECT_LABEL);
}

int		is_label_type(const enum e_token type)
{
	return (type == LABEL || type == INDIRECT_LABEL || type == INDIRECT_LABEL);
}

int		is_num_type(const enum e_token type)
{
	return (type == REG || type == INDIRECT || type == DIRECT);
}

int		check_label(const char *label_name)
{
	size_t		i;

	i = 0;
	while (label_name[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, label_name[i]) == NULL)
			return (FALSE);
		i++;
	}
	return (i != 0);
}

int		is_label_uniq(t_list *label_list, const char *str)
{
	t_token	*label;

	while (label_list != NULL)
	{
		label = (t_token *)(label_list->content);
		if (ft_strequ(str, label->str) == TRUE)
			return (FALSE);
		label_list = label_list->next;
	}
	return (TRUE);
}
