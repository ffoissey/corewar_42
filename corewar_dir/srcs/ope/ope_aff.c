/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:15:37 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:07:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	print_aff(t_carriages *current, int8_t arg_1)
{
	if (ft_printf("Aff : %c\n", current->registres[arg_1 - 1] % 256) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			ope_aff(t_carriages *current, t_data *data)
{
	int8_t	arg_1;

	arg_1 = get_arg(current, data, 1, NO_OCP | REG_FLAG);
	if (data->aff == ON)
		return (print_aff(current, arg_1));
	return (SUCCESS);
}
