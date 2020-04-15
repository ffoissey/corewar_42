/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 13:51:02 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/15 14:32:47 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_token(void *content, size_t content_size)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->str);
	free(token->initial_str);
	free(token);
	(void)content_size;
}

void	exit_routine(void)
{
	t_asm	*env_asm;
	int		ret;

	env_asm = get_env_asm(NULL);
	if (env_asm->a_opt == TRUE)
		debug();
	ret = print_error(env_asm->error, env_asm->token_error);
	if (ret == NO_ERR)
		ft_printf("Writing output program to %s\n", env_asm->cor_file);
	if (env_asm->token_error != NULL)
	{
		ft_strdel(&(env_asm->token_error->str));
		ft_strdel(&(env_asm->token_error->initial_str));
	}
	ft_lstdel(&env_asm->token_list, del_token);
	ft_lstdel(&env_asm->label_list, del_token);
	ft_strdel(&env_asm->name);
	ft_strdel(&env_asm->comment);
	ft_strdel(&env_asm->cor_file);
	vct_del(&env_asm->dquote);
	vct_del(&env_asm->output);
	close(env_asm->fd);
	exit(ret);
}

void	exit_error(const uint64_t err, t_token *token_error)
{
	t_asm	*env_asm;

	env_asm = get_env_asm(NULL);
	env_asm->error |= err;
	env_asm->token_error = token_error;
	exit_routine();
}
