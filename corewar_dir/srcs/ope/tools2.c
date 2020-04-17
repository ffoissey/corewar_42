/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 16:05:45 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 18:14:25 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint16_t	get_pos(int16_t position)
{
	if (position < 0)
		return ((uint16_t)(MEM_SIZE - (-position) % MEM_SIZE));
	return ((uint16_t)(position % MEM_SIZE));
}

int16_t		get_ind_value(t_data *data, int16_t position, int32_t arg,
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
		add = ((uint8_t)data->vm.arena[get_pos(position + i + arg)]);
		add <<= (8 * i) ; // position + TO_JMP ? 
		value |= (int32_t)add;
		i++;
	}
	return (value);
}

int16_t		set_reg_value(t_carriages *current, int8_t reg, uint8_t value,
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

int		ft_isanint(char *str)
{
	long		nb;

	nb = ft_atol(str);
	return (nb <= INT_MAX && nb >= INT_MIN);
}
