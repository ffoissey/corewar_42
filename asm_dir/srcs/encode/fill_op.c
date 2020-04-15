/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 16:43:58 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/15 14:34:29 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		create_mask(const uint16_t mask_in)
{
	char	mask_out;
	uint8_t	i;

	mask_out = 0;
	i = 0;
	while (i < 6)
	{
		if ((mask_in >> (8 - (i * 2))) & T_REG)
			mask_out |= ((REG_MASK << i) << 2);
		else if ((mask_in >> (8 - (i * 2))) & T_DIR)
			mask_out |= ((DIR_MASK << i) << 2);
		else if ((mask_in >> (8 - (i * 2))) & T_IND)
			mask_out |= ((IND_MASK << i) << 2);
		i += 2;
	}
	return (mask_out);
}

static size_t	fill_mask(t_token *op, char *mem_op)
{
	char			mask;

	if (op->mask & IS_OP_CODE)
	{
		mask = create_mask(op->mask);
		ft_memmove(mem_op, &mask, 1);
		return (1);
	}
	return (0);
}

static size_t	fill_arg(t_token *arg, char *mem_op)
{
	char	*mem_part;

	if (arg->type != SPACE && arg->type != SEP)
	{
		if (arg->arg_size == 4)
			arg->value = (int32_t)arg->value;
		else if (arg->arg_size == 2)
			arg->value = (int16_t)arg->value;
		else
			arg->value = (int8_t)arg->value;
		arg->truevalue = arg->value;
		mem_part = (char *)mem_rev((uint8_t *)(&arg->value), arg->arg_size);
		ft_memmove(mem_op, mem_part, arg->arg_size);
		return (arg->arg_size);
	}
	return (0);
}

static size_t	get_op(t_asm *env_asm, char *mem_op)
{
	t_list			*token_list;
	t_token			*op;
	size_t			i;

	token_list = env_asm->op_ptr;
	op = (t_token *)(token_list->content);
	i = 0;
	ft_memmove(mem_op + i++, (char *)(&op->value), 1);
	i += fill_mask(op, mem_op + i);
	token_list = token_list->next;
	while (token_list != NULL && i < op->op_size)
	{
		if (((t_token *)(token_list->content))->type == ENDL)
			break ;
		i += fill_arg((t_token *)token_list->content, mem_op + i);
		token_list = token_list->next;
	}
	env_asm->op_ptr = token_list;
	return (op->op_size);
}

void			fill_with_op(t_vector *output, t_asm *env_asm)
{
	char		mem_op[MAX_LEN_OP];
	size_t		size;

	env_asm->op_ptr = go_to_next_op(env_asm->token_list);
	while (env_asm->op_ptr != NULL)
	{
		env_asm->op_ptr = go_to_next_op(env_asm->op_ptr);
		if (env_asm->op_ptr != NULL)
		{
			ft_bzero(mem_op, MAX_LEN_OP);
			size = get_op(env_asm, mem_op);
			if (vct_addmemat(output, mem_op, size, vct_len(output)) == FAILURE)
				exit_error(MALLOC_ERROR, NULL);
		}
	}
}
