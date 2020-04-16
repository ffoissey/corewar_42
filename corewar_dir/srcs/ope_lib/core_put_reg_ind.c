/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_put_reg_ind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 09:15:24 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 18:36:21 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint16_t	get_pos(int16_t position)
{
	if (position < 0)
		return ((uint16_t)(MEM_SIZE - (-position) % MEM_SIZE));
	return ((uint16_t)(position % MEM_SIZE));
}

uint8_t		core_put_reg_ind(t_data *data, int16_t position, int32_t reg_value)
{
	data->vm.arena[get_pos(position)] = reg_value >> 24;
	data->vm.arena[get_pos(position + 1)] = reg_value >> 16;
	data->vm.arena[get_pos(position + 2)] = reg_value >> 8;
	data->vm.arena[get_pos(position + 3)] = reg_value;
	return (TRUE);
}
