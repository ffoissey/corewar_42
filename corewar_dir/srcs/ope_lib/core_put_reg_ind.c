/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_put_reg_ind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 09:15:24 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 19:03:13 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint8_t		core_put_reg_ind(t_data *data, int16_t position, int32_t reg_value)
{
	data->vm->arena[position % MEM_SIZE] = reg_value >> 24;
	data->vm->arena[(position + 1) % MEM_SIZE] = reg_value >> 16;
	data->vm->arena[(position + 2) % MEM_SIZE] = reg_value >> 8;
	data->vm->arena[(position + 3) % MEM_SIZE] = reg_value;
	return (TRUE);
}
