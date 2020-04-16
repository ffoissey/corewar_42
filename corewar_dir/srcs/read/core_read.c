/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:31:09 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:42:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <stdio.h>

static int8_t			read_header(t_champs *champs, int32_t fd)
{
	unsigned char	magic[4];
	ssize_t			ret;
	int32_t			header;

	ret = read(fd, magic, 4);
	if (ret == FAILURE)
		return (core_error(10));
	if (ret == 4)
	{
		header = (magic[0] << 24 | magic[1] << 16 | magic[2] << 8
			| magic[3]);
		if (header == COREWAR_EXEC_MAGIC)
			return (SUCCESS);
	}
	if (ft_putstr_fd(champs->file_path, STDERR_FILENO) == FAILURE)
		return (core_error(8));
	return (core_error(3));
}

static int8_t			read_name(t_champs *champs, int32_t fd)
{
	ssize_t			ret;

	ret = read(fd, champs->name, PROG_NAME_LENGTH);
	if (ret == FAILURE)
		return (core_error(10));
	if (ret != PROG_NAME_LENGTH)
	{
		if (ft_putstr_fd(champs->name, STDERR_FILENO) == FAILURE)
			return (core_error(8));
		return (core_error(4));
	}
	return (SUCCESS);
}

static	int8_t			skip_null(t_champs *champs, int32_t fd)
{
	ssize_t			ret;
	unsigned char	buff[4];

	ret = read(fd, buff, 4);
	if (ret == FAILURE)
		return (core_error(10));
	if (buff[0] == 0 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
		return (SUCCESS);
	if (ft_putstr_fd(champs->name, STDERR_FILENO) == FALSE)
		return (core_error(8));
	return (core_error(5));
}

static int8_t			core_open_management(t_champs *champs,
						t_data *data, int8_t champ_nb)
{
	int32_t		fd;

	errno = 0;
	fd = open(champs->file_path, O_RDONLY);
	if (fd < 0)
	{
		if (ft_putstr_fd(champs->file_path, STDERR_FILENO) == FAILURE
		|| ft_putstr_fd(" : ", STDERR_FILENO) == FAILURE)
			return (core_error(8));
		perror(NULL);
		return (FAILURE);
	}
	if ((read_header(champs, fd) == FAILURE)
		|| (read_name(champs, fd) == FAILURE)
		|| (skip_null(champs, fd) == FAILURE)
		|| (core_read_exec_code_size(champs, fd) == FAILURE)
		|| (core_read_comment(champs, fd) == FAILURE)
		|| (skip_null(champs, fd) == FAILURE)
		|| (core_install_champ(champs, fd, data, champ_nb) == FAILURE))
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}

int8_t					core_read(t_data *data)
{
	int8_t		count;
	int8_t		champ_nb;

	champ_nb = 0;
	count = -1;
	while (++count < 4)
	{
		if (data->champs[count])
		{
			if (core_open_management(data->champs[count],
					data, champ_nb) == FAILURE)
			{
				core_free_all(data);
				return (FAILURE);
			}
			champ_nb++;
		}
	}
	if (core_init_data_vm(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
