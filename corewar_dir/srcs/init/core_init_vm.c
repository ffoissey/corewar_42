/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_vm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:00:13 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/22 16:30:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void			core_install_champ(t_champs *champs,
				int32_t fd, t_data *data, int8_t champ_nb)
{
	ssize_t			ret;
	unsigned char		tmp_code[CHAMP_MAX_SIZE];
	int32_t			count_cpy;

	count_cpy = 0;
	errno = 0;
	ft_bzero((void *)tmp_code, CHAMP_MAX_SIZE);
	ret = read(fd, tmp_code, (size_t)champs->exec_code_size);
	if (ret == FAILURE)
	{
		ft_dprintf(STDERR_FILENO, "\033[1;31mERROR:\033[0m %s : ",
			champs->name);
		core_error(get_env_data(DATA), ER_READ);
	}
	if (ret != champs->exec_code_size)
	{
		ft_dprintf(STDERR_FILENO, "\033[1;31mERROR:\033[0m %s : ",
			champs->name);
		core_error(data, ER_DIFF);
	}
	champs->copy_start = (MEM_SIZE / data->initialised_players) * (champ_nb);
	while (count_cpy < champs->exec_code_size)
		data->vm.arena[champs->copy_start++] = (uint8_t)tmp_code[count_cpy++];
	champs->copy_start = champs->copy_start - champs->exec_code_size;
}

void			core_init_data_vm(t_data *data)
{
	int8_t	count;

	count = MAX_PLAYERS - 1;
	while (data->champs[count] == NULL && count >= 0)
		count--;
	if (count < 0)
	{
		ft_dprintf(STDERR_FILENO, "\033[1;31mERROR: \033[0m");
		core_error(data, ER_INIT);
	}
	data->vm.last_alive_champ = (uint8_t)(count + 1);
	data->vm.cycles_to_die = CYCLE_TO_DIE;
	data->vm.cycle_last_check = 1;
}
