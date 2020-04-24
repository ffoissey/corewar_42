/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:41:52 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/24 17:10:23 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint16_t	get_pos(int16_t position)
{
	if (position < 0)
		return ((uint16_t)(MEM_SIZE - (-position) % MEM_SIZE));
	return ((uint16_t)(position % MEM_SIZE));
}

int32_t		get_ind_value(t_data *data, uint16_t position, int16_t arg,
					uint16_t flag)
{
	uint8_t		i;
	uint8_t		max;
	int32_t		value;
	int64_t		add;

	i = 0;
	max = (flag & IND) ? 4 : 2;
	value = 0;
	while (i < max)
	{
		add = (data->vm.arena[get_pos(arg + i + position)] & 0xff);
		add <<= (8 * (max - 1 - i));
		value |= (add & 0xffffffff);
		i++;
	}
	if ((flag & IND) == FALSE)
		value = value;
	return (value);
}

int32_t		set_reg_value(t_carriages *current, uint8_t reg, int32_t value,
				uint8_t *flag)
{
	if (reg > 0 && reg <= REG_NUMBER)
	{
		if (*flag & SET)
			current->registres[reg - 1] = value;
		return (current->registres[reg - 1]);
	}
	*flag = BAD_REG;
	return (FAILURE);
}
