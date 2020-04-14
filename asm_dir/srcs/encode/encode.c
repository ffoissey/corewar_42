/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 16:43:58 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 16:14:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint8_t		*mem_rev(uint8_t *mem, size_t size)
{
	size_t		i;
	char		tmp;

	i = 0;
	if (size < 2)
		return (mem);
	size--;
	while (i <= size)
	{
		tmp = mem[size];
		mem[size] = mem[i];
		mem[i] = tmp;
		size--;
		i++;
	}
	return (mem);
}

size_t		fill_vector(t_vector *output, char *s, size_t len, size_t offset)
{
	vct_addmemat(output, s, len, offset);
	return (offset + len);
}

static void	fill_output(t_vector *output, t_asm *env_asm)
{
	static uint32_t	magic_header = COREWAR_EXEC_MAGIC;
	char			*str_magic_header;
	char			*str_mem_size;
	static char		empty[4] = "";
	size_t			offset;

	(void)env_asm;
	offset = 0;
	str_magic_header = (char *)mem_rev((uint8_t *)(&magic_header), 4);
	str_mem_size = (char *)mem_rev((uint8_t *)(&env_asm->mem_count), 4);
	offset = fill_vector(output, str_magic_header, 4, offset);
	offset = fill_vector(output, env_asm->name, PROG_NAME_LENGTH, offset);
	offset = fill_vector(output, empty, 4, offset);
	offset = fill_vector(output, str_mem_size, 4, offset);
	offset = fill_vector(output, env_asm->comment, PROG_COMMENT_LENGTH, offset);
	fill_vector(output, empty, 4, offset);
	fill_with_op(output, env_asm);
}

t_vector	*encoding(t_asm *env_asm)
{
	t_vector	*output;
	size_t		header_size;

	header_size = 4 + PROG_NAME_LENGTH + 4 + 4 + PROG_COMMENT_LENGTH;
	output = vct_new(header_size + env_asm->mem_count + DFL_VCT_SIZE);
	fill_output(output, env_asm);
	return (output);
}
