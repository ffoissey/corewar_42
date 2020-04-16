/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:18:10 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 21:21:05 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			ope_st(t_carriages *current, t_data *data)
{
	int32_t		arg[2];
	uint8_t		ocp;

	ocp = core_get_ocp(data, current->position + current->to_jump);
	arg[0] = get_arg(current, data, 1, NO_NEED);
	arg[1] = get_arg(current, data, 2, IND);
	if (ocp == REG_REG_)
		current->registres[arg[1] - 1] = arg[0];
	else if (arg[0] > 0 && arg[0] <= REG_NUMBER)
		core_put_reg_ind(data, get_pos(current->position + arg[1]) % IDX_MOD,
			current->registres[arg[0] - 1]);
	else
		return (FAILURE); //exit
	return (SUCCESS);
}
