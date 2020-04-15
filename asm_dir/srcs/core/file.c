/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:02:27 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/15 16:02:35 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	get_file_fd(t_asm *env_asm, const char *name)
{
	size_t	len;

	len = (name == NULL) ? 0 : ft_strlen(name);
	if (len > LEN_EXTENSION)
	{
		if (ft_strequ(name + len - LEN_EXTENSION, EXTENSION) == FALSE)
			exit_error(BAD_EXTENSION, NULL);
		env_asm->fd = open(name, O_RDONLY);
		if (env_asm->fd == FAILURE)
			exit_error(OPEN_ERROR, NULL);
	}
	else if (len != 0 && ft_strequ(name, EXTENSION) == TRUE)
		exit_error(NO_FILE_NAME, NULL);
	else if (len != 0 && ft_strchr(name, '.') != NULL)
		exit_error(BAD_EXTENSION, NULL);
	exit_error(BAD_EXTENSION, NULL);
}

void	write_file(t_asm *env_asm, char *name)
{
	int		fd;
	size_t	len;

	len = ft_strlen(name);
	name[len - LEN_EXTENSION] = '\0';
	env_asm->cor_file = ft_strjoin(name, EXTENSION_COR);
	if (env_asm->cor_file == NULL)
		exit_error(MALLOC_ERROR, NULL);
	fd = open(env_asm->cor_file, O_CREAT | O_WRONLY,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd != FAILURE)
	{
		if (vct_print_fd(env_asm->output, fd) == FAILURE)
			exit_error(WRITE_ERROR, NULL);
	}
	else
		exit_error(OPEN_ERROR, NULL);
	close(fd);
}
