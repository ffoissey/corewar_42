/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ind_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:50:47 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 19:06:09 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int32_t		core_ind_value(t_data *data, int16_t position, int32_t ind)
{
	int32_t value;

	ind = ind % IDX_MOD;
	value = 0;
	value |= (unsigned char)data->vm->arena[(position + ind) % MEM_SIZE];
	value <<= 8;
	value |= (unsigned char)data->vm->arena[(position + ind + 1) % MEM_SIZE];
	value <<= 8;
	value |= (unsigned char)data->vm->arena[(position + ind + 2) % MEM_SIZE];
	value <<= 8;
	value |= (unsigned char)data->vm->arena[(position + ind + 3) % MEM_SIZE];
	return (value);
}
