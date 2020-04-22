/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_and_binary_ope.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:07:10 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/22 15:20:58 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
*** ADD 0x04
*/

int8_t		ope_add(t_carriages *current, t_data *data)
{
	return (do_op(current, data, OP_ADD));
}

/*
*** SUB 0x05
*/

int8_t		ope_sub(t_carriages *current, t_data *data)
{
	return (do_op(current, data, OP_SUB));
}

/*
*** AND 0x06
*/

int8_t		ope_and(t_carriages *current, t_data *data)
{
	return (do_op(current, data, OP_AND));
}

/*
*** OR 0x07
*/

int8_t		ope_or(t_carriages *current, t_data *data)
{
	return (do_op(current, data, OP_OR));
}

/*
*** XOR 0x08
*/

int8_t		ope_xor(t_carriages *current, t_data *data)
{
	return (do_op(current, data, OP_XOR));
}
