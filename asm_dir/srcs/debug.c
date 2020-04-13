/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:44:35 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/12 14:56:04 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	debug_list_label(t_asm *env_asm)
{
	t_token		*label;
	t_list		*label_list;

	label_list = env_asm->label_list;
	ft_printf("\033[36m\n < LABEL LIST > \n\033[0m\n");
	while (label_list != NULL)
	{
		label = (t_token *)(label_list->content);
		ft_printf("%10s -> ", label->str);
		ft_printf(" line: %3zu, col: %3zu, offset: %#10d\n", label->line, label->col, label->mem_offset);
		label_list = label_list->next;
	}
	ft_printf("\033[36m\n < END LABEL LIST > \n\033[0m\n");
}

void	debug_list_token(t_asm *env_asm, int flag)
{
	t_token		*token;
	t_list		*token_list;
	const char	*noname_token[] = {"reg",
						"ind label", "dir", "dir label", "SEP",
						"TAB", "SPACE", "ENDL"};
	const char	*color[] = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};
	const char	*endc	= "\033[0m";
	

	token_list = env_asm->token_list;
	ft_printf("\033[32m\n < DEBUG TOKEN >\n\033[0m\n");
	while (token_list != NULL)
	{
		token = (t_token *)(token_list->content);
		
		if (flag == SKIP_SPACESEP && (token->type == SPACE || token->type == SEP))
		{
			token_list = token_list->next;
			continue ;
		}
		else if (token->type == ENDL) 
		{
			ft_printf("< - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - >\n");
			token_list = token_list->next;
			continue ;
		}
		if (token->type == COMMENT_HASH || token->type == COMMENT_SEMICOLON)
			return ;
		if (token->type == UNKNOW)
			ft_printf("|%s%10s%s -> ", color[0], "UNKNOW", endc);
		else if (token->type == STRING)
			ft_printf("|%s%10s%s -> ", color[5], "STRING", endc);
		else if (token->type == SPACE)
			ft_printf("|%s%10s%s -> ", color[1], noname_token[token->type - 19], endc);
		else if (token->type == SEP)
			ft_printf("|%s%10s%s -> ", color[4], noname_token[token->type - 19], endc);
		else if (token->type >= 19 && token->type <= 26)
			ft_printf("|%s%10s%s -> ", color[2], noname_token[token->type - 19], endc);
		else
			ft_printf("|%s%10s%s -> ", color[3], env_asm->grammar[token->type], endc);
		if (token->type == STRING)
			ft_printf("%*s\"%s\"", ft_strlen(token->str) > 10 ? 0 : 10 - ft_strlen(token->str), " ", token->str);
		else if (token->str != NULL
				&& (token->str[0] == '\t' || token->str[0] == '\n'))
			ft_printf("%12s", token->str[0] == '\n' ? "\\n" : "\\t");
		else
			ft_printf("%12s", token->str); // DEBUG		
		if (token->type == DIRECT || token->type == INDIRECT
			|| token->type == REG || token->type == INDIRECT_LABEL
			|| token->type == DIRECT_LABEL)
			ft_printf(" | Value: %12d |", token->value);
		else
			ft_printf(" |        %12s |", "            ");
		ft_printf(" line: %3zu, col: %3zu, offset: %#10d\n", token->line, token->col, token->mem_offset);
		token_list = token_list->next;
	}
	ft_printf("\033[32m\n < END DEBUG TOKEN >\033[0m\n\n");
}

void	debug_comment(t_vector *line)
{
	char * str;
	
	str = ft_strchr(vct_getstr(line), '#');
	if (str == NULL)
		str = ft_strchr(vct_getstr(line), ';');
	if (str != NULL)
		ft_printf("comment: %s\n", str + 1);
}

void	debug(t_asm *env_asm, int flag)
{
	debug_list_token(env_asm, flag); // DEBUG LIST TOKEN
	debug_list_label(env_asm); // DEBUG LIST LABEL
	ft_printf("Champion name    : \"%s\"\nChampion comment : \"%s\"\n", env_asm->name, env_asm->comment);
}
