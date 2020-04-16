/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_ind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:42:12 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:46:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int16_t		core_get_ind(t_data *data, int16_t position)
{
	int16_t		ind;

	ind = (data->vm.arena[position % MEM_SIZE] << 8 |
		data->vm.arena[(position + 1) % MEM_SIZE]);
	return (ind);
}
