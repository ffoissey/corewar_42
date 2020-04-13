/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:03:28 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 18:58:36 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int32_t		core_get_dir(t_data *data, int16_t position)
{
	int32_t		dir;
	t_vm		*vm;

	vm = data->vm;
	dir = (vm->arena[position % MEM_SIZE] << 24
		| vm->arena[(position + 1) % MEM_SIZE] << 16
		| vm->arena[(position + 2) % MEM_SIZE] << 8
		| vm->arena[(position + 3) % MEM_SIZE]);
	return (dir);
}
