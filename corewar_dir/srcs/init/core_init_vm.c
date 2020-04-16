/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_vm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:00:13 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 16:55:04 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			core_install_champ(t_champs *champs,
				int32_t fd, t_data *data, int8_t champ_nb)
{
	ssize_t			ret;
	unsigned char	tmp_code[champs->exec_code_size];
	int32_t			count_cpy;

	count_cpy = 0;
	ret = read(fd, tmp_code, champs->exec_code_size);
	if (ret == FAILURE)
		return (core_error(ER_READ));
	if (ret != champs->exec_code_size)
		return (FAILURE);
	champs->copy_start = (MEM_SIZE / data->initialised_players) * (champ_nb);
	while (count_cpy < champs->exec_code_size)
		data->vm.arena[champs->copy_start++] = (uint8_t)tmp_code[count_cpy++];
	champs->copy_start = champs->copy_start - champs->exec_code_size;
	return (SUCCESS);
}

int8_t			core_init_data_vm(t_data *data)
{
	uint8_t	count;

	if (data->champs[0] == NULL)
		return (FAILURE);
	count = 0;
	while (data->champs[count] != NULL)
		count++;
	data->vm.last_alive_champ = count - 1;
	data->vm.cycles_to_die = CYCLE_TO_DIE;
	data->vm.cycle_last_check = 1;
	return (SUCCESS);
}

