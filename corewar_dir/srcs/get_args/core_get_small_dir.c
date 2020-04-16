/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_small_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 10:29:11 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:47:13 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int16_t		core_get_small_dir(t_data *data, int16_t position)
{
	int16_t		dir;

	dir = (data->vm.arena[position % MEM_SIZE] << 8
		| data->vm.arena[(position + 1) % MEM_SIZE]);
	return (dir);
}
