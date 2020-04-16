/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_reg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:46:46 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:46:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		core_get_reg(t_data *data, int16_t position)
{
	int8_t		reg;

	reg = (data->vm.arena[position % MEM_SIZE]);
	if (reg > 0 && reg < 17)
		return (reg);
	return (FAILURE);
}
