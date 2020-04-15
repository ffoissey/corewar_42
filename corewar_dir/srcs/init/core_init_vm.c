/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init_vm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:00:13 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 16:55:46 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			core_install_champ(t_champs *champs,
				int32_t fd, t_data *data, int8_t champ_nb)
{
	int32_t			ret;
	unsigned char	tmp_code[champs->exec_code_size];
	int32_t			count_cpy;

	count_cpy = 0;
	ret = read(fd, tmp_code, champs->exec_code_size);
	if (ret != champs->exec_code_size)
		return (FAILURE);
	champs->copy_start = (MEM_SIZE / data->initialised_players) * (champ_nb);
	while (count_cpy < champs->exec_code_size)
		data->vm->arena[champs->copy_start++] = (uint8_t)tmp_code[count_cpy++];
	champs->copy_start = champs->copy_start - champs->exec_code_size;
	return (SUCCESS);
}

int8_t			core_init_data_vm(t_data *data)
{
	int8_t count;

	count = 3;
	while (data->champs[count] == NULL && count >= 0)
		count--;
	if (count < 0)
		return (FAILURE);
	data->vm->last_alive_champ = count;
	data->vm->cycles_to_die = CYCLE_TO_DIE;
	return (SUCCESS);
}

int8_t			core_init_vm(t_data *data)
{
	t_vm		*vm;

	vm = (t_vm *)ft_memalloc(sizeof(t_vm));
	if (vm == NULL)
		return (core_error(1));
	ft_bzero(vm->arena, MEM_SIZE);
	vm->cycle_last_check = 1;
	data->vm = vm;
	return (SUCCESS);
}
