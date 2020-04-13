/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_reg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:46:46 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 18:59:16 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		core_get_reg(t_data *data, int16_t position)
{
	int8_t		reg;
	t_vm		*vm;

	vm = data->vm;
	reg = (vm->arena[position % MEM_SIZE]);
	if (reg > 0 && reg < 17)
		return (reg);
	return (FAILURE);
}
