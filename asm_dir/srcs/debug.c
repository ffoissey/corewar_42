/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:44:35 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/14 14:36:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	debug_list_label(t_asm *env_asm)
{
	t_token		*label;
	t_list		*label_list;

	label_list = env_asm->label_list;
	while (label_list != NULL)
	{
		label = (t_token *)(label_list->content);
		ft_printf("%10s -> ", label->str);
		ft_printf(" line: %3zu, col: %3zu, offset: %#10d\n",
				label->line, label->col, label->mem_offset);
		label_list = label_list->next;
	}
}

static int	is_sep_or_endl(enum e_token type)
{
	return (type == SPACE || type == SEP || type == ENDL);
}

static void	print_debug_token(t_asm *env_asm, t_token *token)
{
	static const char	*noname_token[] = {"reg", "ind label", "dir",
											"dir label"};
	static const char	*color[] = {"\033[31m", "\033[32m", "\033[33m",
									"\033[34m", "\033[35m", "\033[36m",
									"\033[0m"};

	if (token->type == UNKNOW)
		ft_printf("   |%s%10s%s -> ", color[0], "UNKNOW", color[6]);
	else if (token->type == STRING)
		ft_printf("   |%s%10s%s -> ", color[1], "STRING", color[6]);
	else if (token->type >= 19 && token->type <= 23)
		ft_printf("   |%s%10s%s -> ", color[2], noname_token[token->type - 19],
				color[6]);
	else
		ft_printf("   |%s%10s%s    ", color[3], env_asm->grammar[token->type],
				color[6]);
	if (token->type == STRING)
		ft_printf(" | %sValue:%s %30s |", color[0], color[6], token->str);
	else if (is_arg_type(token->type) == TRUE)
		ft_printf(" | %sValue:%s %30d |", color[0], color[6], token->truevalue);
	else
		ft_printf(" |        %30s |", "            ");
	ft_printf(" %sline:%s %3zu | %scol:%s %3zu | %soffset:%s %#10d\n",
					color[4], color[6], token->line, color[4], color[6],
					token->col, color[5], color[6], token->mem_offset);
}

static void	debug_list_token(t_asm *env_asm)
{
	t_token		*token;
	t_list		*token_list;

	token_list = env_asm->token_list;
	while (token_list != NULL)
	{
		token = (t_token *)(token_list->content);
		if (is_sep_or_endl(token->type) == FALSE)
			print_debug_token(env_asm, token);
		else if (token->type == ENDL)
		{
			ft_printf("< - - - - - - - - - - - - - - - - - - - - - - - - - - ");
			ft_printf("- - - - - - - - - - - - - - - - - - - - - - - - - >\n");
		}
		token_list = token_list->next;
	}
}

void		debug(void)
{
	t_asm	*env_asm;

	env_asm = get_env_asm(NULL);
	ft_printf("\033[32m\n < DEBUG TOKEN >\n\033[0m\n");
	debug_list_token(env_asm);
	ft_printf("\033[32m\n < END DEBUG TOKEN >\033[0m\n\n");
	ft_printf("\033[36m\n < LABEL LIST > \n\033[0m\n");
	debug_list_label(env_asm);
	ft_printf("\033[36m\n < END LABEL LIST > \n\033[0m\n");
}
