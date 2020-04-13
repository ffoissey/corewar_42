/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:02:27 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/13 17:19:00 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	get_file_fd(t_asm *env_asm, char *name)
{
	size_t	len;

	len = (name == NULL) ? 0 : ft_strlen(name);
	if (len > LEN_EXTENSION)
	{
		if (ft_strequ(name + len - LEN_EXTENSION, EXTENSION) == TRUE)
		{
			if (env_asm->fd < 0)
				exit_error(BAD_FD, NULL);
			env_asm->fd = open(name, O_RDONLY);
			if (env_asm->fd == FAILURE)
				exit_error(OPEN_ERROR, NULL);
		}
		else
			exit_error(BAD_EXTENSION, NULL);
	}
	else
		exit_error(NO_FILE_NAME, NULL);
}

void	write_file(t_vector *vct, char *name)
{
	int		fd;
	size_t	len;
	char	*new_file;

	len = ft_strlen(name);
	name[len - LEN_EXTENSION] = '\0';
	new_file = ft_strjoin(name, EXTENSION_COR);
	if (new_file == NULL)
		exit_error(MALLOC_ERROR, NULL);
	fd = open(new_file, O_CREAT | O_WRONLY,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd != FAILURE)
	{
		if (vct_print_fd(vct, fd) == FAILURE)
			exit_error(WRITE_ERROR, NULL);
	}
	else
		exit_error(OPEN_ERROR, NULL);
	close(fd);
	ft_printf("Writing output program to %s\n", new_file);
	ft_strdel(&new_file);
}
