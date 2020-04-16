/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:18:10 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 22:19:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t			ope_st(t_carriages *current, t_data *data)
{
	int32_t		arg[2];
	uint8_t		ocp;
	int8_t		reg_value;

	ocp = core_get_ocp(data, current->position + current->to_jump);
	arg[0] = get_arg(current, data, 1, NO_NEED);
	arg[1] = get_arg(current, data, 2, IND);
	if (ocp == REG_REG_)
		set_reg_value(current, arg[1], arg[0], SET);
	reg_value = set_reg_value(current, arg[0], NO_NEED, GET);
	if (reg_value == FAILURE)
		return (FAILURE);
	core_put_reg_ind(data, get_pos(current->position + arg[1]) % IDX_MOD, reg_value);
	return (SUCCESS);
}
