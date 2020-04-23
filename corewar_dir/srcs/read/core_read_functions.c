/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_read_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:03:58 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/22 16:31:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		core_read_exec_code_size(t_champs *champs, int32_t fd)
{
	ssize_t			ret;
	int32_t			size;
	unsigned char	buff[4];

	ret = read(fd, buff, 4);
	if (ret == FAILURE)
		core_error(get_env_data(DATA), ER_READ);
	if (ret != 4)
	{
		if (ft_putstr_fd(champs->name, STDERR_FILENO) == FAILURE)
			core_error(get_env_data(DATA), ER_STDCLOSED);
		core_error(get_env_data(DATA), ER_SMALL);
	}
	size = (buff[0] << 24 | buff[1] << 16 | buff[2] << 8 | buff[3]);
	if (size < 0 || size > CHAMP_MAX_SIZE)
	{
		if (ft_putstr_fd(champs->name, STDERR_FILENO) == FAILURE)
			core_error(get_env_data(DATA), ER_STDCLOSED);
		core_error(get_env_data(DATA), ER_BIG);
	}
	champs->exec_code_size = size;
}

void		core_fd_empty(int32_t fd)
{
	ssize_t			ret;
	unsigned char	read_test[2];

	ret = read(fd, read_test, 2);
	if (ret != 0)
		core_error(get_env_data(DATA), ER_DIFF);
}

void		core_read_comment(t_champs *champs, int32_t fd)
{
	ssize_t		ret;

	ret = read(fd, champs->comment, COMMENT_LENGTH);
	if (ret == FAILURE)
		core_error(get_env_data(DATA), ER_READ);
	if (ret != COMMENT_LENGTH)
		core_error(get_env_data(DATA), ER_SIZE_COMM);
	champs->comment[ret] = '\0';
}
