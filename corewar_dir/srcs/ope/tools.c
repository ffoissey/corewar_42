/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 16:04:32 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 16:11:18 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint8_t		core_put_reg_ind(t_data *data, int16_t position, int32_t reg_value)
{
	data->vm.arena[get_pos(position)] = reg_value >> 24;
	data->vm.arena[get_pos(position + 1)] = reg_value >> 16;
	data->vm.arena[get_pos(position + 2)] = reg_value >> 8;
	data->vm.arena[get_pos(position + 3)] = reg_value;
	return (TRUE);
}

int32_t		core_get_dir(t_data *data, int16_t position, uint16_t flag)
{
	int32_t		dir;

	if (flag & SMALL_DIR)
	{
		dir = (data->vm.arena[position % MEM_SIZE] << 8
			| data->vm.arena[(position + 1) % MEM_SIZE]);
		return (dir);
	}
	else
	{
		dir = (data->vm.arena[position % MEM_SIZE] << 24
			| data->vm.arena[(position + 1) % MEM_SIZE] << 16
			| data->vm.arena[(position + 2) % MEM_SIZE] << 8
			| data->vm.arena[(position + 3) % MEM_SIZE]);
	}
	return (dir);
}

int16_t		core_get_ind(t_data *data, int16_t position, int16_t to_jump,
				uint16_t flag)
{
	int16_t		ind;
	int16_t		jump_pos;

	jump_pos = get_pos(position + to_jump);
	ind = (data->vm.arena[jump_pos] << 8 | data->vm.arena[get_pos(jump_pos + 1)]);
	return (get_ind_value(data, position, ind % IDX_MOD, flag));
}

int16_t		core_get_reg(t_data *data, int16_t position, t_carriages *current)
{
	int16_t		reg;

	reg = (data->vm.arena[get_pos(position)]);
	if (reg > 0 && reg <= REG_NUMBER)
		return (current->registres[reg - 1]);
	return (FAILURE);
}

uint8_t		core_get_ocp(t_data *data, int16_t position)
{
	return (data->vm.arena[get_pos(position)]);
}
