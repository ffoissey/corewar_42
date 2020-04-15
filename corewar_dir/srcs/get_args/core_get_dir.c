/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:03:28 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:46:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int32_t		core_get_dir(t_data *data, int16_t position)
{
	int32_t		dir;

	dir = (data->vm.arena[position % MEM_SIZE] << 24
		| data->vm.arena[(position + 1) % MEM_SIZE] << 16
		| data->vm.arena[(position + 2) % MEM_SIZE] << 8
		| data->vm.arena[(position + 3) % MEM_SIZE]);
	return (dir);
}
