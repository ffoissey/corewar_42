/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:28:13 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 17:23:13 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		size_of_arg(enum e_token op_type, t_token *arg,
				uint16_t *arg_code, int shift)
{
	const uint16_t	size[4] = {T_REG, T_IND, T_DIR, T_DIR};
	const uint8_t	dir[] = {0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};
	int				scale;
	int				code;

	code = 0;
	if (op_type > NB_OP)
		exit_error(BAD_TOKEN, arg);
	if (arg->type == INDIRECT)
		code = T_IND;
	else if ((scale = arg->type - 19) >= 0 && scale < 4)
		code = size[scale];
	else
		exit_error(BAD_TOKEN, arg);
	*arg_code |= (code << shift);
	if (code == T_REG)
		return ((arg->arg_size = 1));
	else if (code == T_IND)
		return ((arg->arg_size = IND_SIZE));
	return ((arg->arg_size = dir[op_type]));
}

static ssize_t	parse_op_arg(t_list *token_list, enum e_token op_type,
					uint16_t *arg_code, t_token *op)
{
	t_token		*token;
	ssize_t		mem_offset;
	uint8_t		count;

	mem_offset = 0;
	count = 0;
	token = (t_token *)(token_list->content);
	if (token->type != SPACE)
		exit_error(BAD_ARG_OP, op);
	while (token_list != NULL && token->type != ENDL)
	{
		if (token->type != SPACE)
		{
			if (count % 2 == 0)
				mem_offset += size_of_arg(op_type, token, arg_code, count * 2);
			else if (token->type != SEP || count > MAX_ARG + 1)
				exit_error(BAD_TOKEN, token);
			count++;
		}
		token_list = token_list->next;
		token = (t_token *)(token_list->content);
	}
	return (mem_offset);
}

void			op_checker(t_asm *env_asm)
{
	const uint16_t	op_arg[NB_OP + 1] = {NO_OP_ARG, LIVE_ARG, LD_ARG, ST_ARG,
								ADD_ARG, SUB_ARG, AND_ARG, OR_ARG, XOR_ARG,
								ZJMP_ARG, LDI_ARG, STI_ARG, FORK_ARG, LLD_ARG,
								LLDI_ARG, LFORK_ARG, AFF_ARG};
	uint16_t		arg_code;
	int				mem_offset;
	t_token			*op;

	arg_code = 0;
	op = (t_token *)((env_asm->op_ptr)->content);
	op->value = op->type;
	mem_offset = (int)parse_op_arg(env_asm->op_ptr->next, op->type,
					&arg_code, op);
	if (arg_code == 0 || (op_arg[op->type] ^ arg_code) & arg_code)
		exit_error(BAD_ARG_OP, op);
	mem_offset++;
	if (op_arg[op->type] & IS_OP_CODE)
	{
		op->mask = arg_code | IS_OP_CODE;
		mem_offset++;
	}
	op->op_size = mem_offset;
	env_asm->mem_count += (size_t)mem_offset;
	env_asm->op_ptr = NULL;
}
