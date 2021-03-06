/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:01 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 15:18:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
**** LD 0x02
*/

int8_t			ope_ld(t_carriages *current, t_data *data)
{
	return (load_value(current, data, OP_LD));
}

/*
**** LLD 0x0d
*/

int8_t			ope_lld(t_carriages *current, t_data *data)
{
	return (load_value(current, data, OP_LLD));
}

/*
**** LDI 0x0a
*/

int8_t			ope_ldi(t_carriages *current, t_data *data)
{
	return (load_indvalue(current, data, OP_LDI));
}

/*
**** LLDI 0x0e
*/

int8_t			ope_lldi(t_carriages *current, t_data *data)
{
	return (load_indvalue(current, data, OP_LLDI));
}
