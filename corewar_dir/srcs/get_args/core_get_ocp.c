/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_get_ocp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:24:53 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:36:50 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

uint8_t		core_get_ocp(t_data *data, int16_t position)
{
	uint8_t		ocp;

	ocp = data->vm.arena[position % MEM_SIZE];
	return (ocp);
}
