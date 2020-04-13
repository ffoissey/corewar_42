/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_ind_value_lld.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:30:27 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 19:06:34 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int16_t		core_ind_value_lld(t_data *data, int16_t position, int32_t ind)
{
	int16_t value;

	value = 0;
	value |= (unsigned char)data->vm->arena[(position + ind) % MEM_SIZE];
	value <<= 8;
	value |= (unsigned char)data->vm->arena[(position + ind + 1) % MEM_SIZE];
	return (value);
}
