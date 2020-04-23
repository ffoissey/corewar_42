/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:31:09 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/22 16:49:03 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <stdio.h>

static void			read_header(t_champs *champs, int32_t fd)
{
	unsigned char	magic[4];
	ssize_t			ret;
	int64_t			header;

	ret = read(fd, magic, 4);
	if (ret == FAILURE)
		core_error(get_env_data(DATA), ER_READ);
	if (ret == 4)
	{
		header = ((long)(magic[0]) << 24 | magic[1] << 16 | magic[2] << 8
			| magic[3]);
		if (header == COREWAR_EXEC_MAGIC)
			return ;
	}
	if (ft_putstr_fd(champs->file_path, STDERR_FILENO) == FAILURE)
		core_error(get_env_data(DATA), ER_STDCLOSED);
	core_error(get_env_data(DATA), ER_MAGIC);
}

static void			read_name(t_champs *champs, int32_t fd)
{
	ssize_t			ret;

	ret = read(fd, champs->name, PROG_NAME_LENGTH);
	if (ret == FAILURE)
		core_error(get_env_data(DATA), ER_READ);
	if (ret != PROG_NAME_LENGTH)
	{
		if (ft_putstr_fd(champs->name, STDERR_FILENO) == FAILURE)
			core_error(get_env_data(DATA), ER_STDCLOSED);
		core_error(get_env_data(DATA), ER_NAME);
	}
}

static	void			skip_null(t_champs *champs, int32_t fd)
{
	ssize_t			ret;
	unsigned char	buff[4];

	ret = read(fd, buff, 4);
	if (ret == FAILURE)
		core_error(get_env_data(DATA),ER_READ);
	if (buff[0] == 0 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
		return ;
	if (ft_putstr_fd(champs->name, STDERR_FILENO) == FALSE)
		core_error(get_env_data(DATA), ER_STDCLOSED);
	core_error(get_env_data(DATA),ER_NULL);
}

static void			core_open_management(t_champs *champs,
						t_data *data, int8_t champ_nb)
{
	int32_t		fd;

	errno = 0;
	fd = open(champs->file_path, O_RDONLY);
	if (fd < 0)
	{
		if (ft_putstr_fd(champs->file_path, STDERR_FILENO) == FAILURE
		|| ft_putstr_fd(" : ", STDERR_FILENO) == FAILURE)
			core_error(data, ER_STDCLOSED);
		perror(NULL);
		core_error(data, ER_OPEN);
	}
	read_header(champs, fd);
	read_name(champs, fd);
	skip_null(champs, fd);
	core_read_exec_code_size(champs, fd);
	core_read_comment(champs, fd);
	skip_null(champs, fd);
	core_install_champ(champs, fd, data, champ_nb);
	core_fd_empty(fd);
	close(fd);
}

void				core_read(t_data *data)
{
	int8_t		count;
	int8_t		champ_nb;

	champ_nb = 0;
	count = -1;
	while (++count < 4)
	{
		if (data->champs[count])
		{
			core_open_management(data->champs[count], data, champ_nb);
			champ_nb++;
		}
	}
	core_init_data_vm(data);
}
