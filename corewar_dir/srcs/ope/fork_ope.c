/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:11:59 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/24 16:42:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_carriages	*get_new_carriage(t_carriages *current, uint16_t position,
									int32_t id)
{
	t_carriages		*new;
	uint8_t			nb_reg;

	new = (t_carriages *)ft_memalloc(sizeof(t_carriages));
	if (new != NULL)
	{
		new->position = get_pos((int16_t)position);
		new->id = id;
		new->carry = current->carry;
		new->last_live_cycle = current->last_live_cycle;
		nb_reg = 0;
		while (nb_reg < REG_NUMBER)
		{
			new->registres[nb_reg] = current->registres[nb_reg];
			nb_reg++;
		}
	}
	return (new);
}

static void			add_carriage(t_carriages *new, t_data *data)
{
	if (data->carriages != NULL)
	{
		data->carriages->previous = new;
		new->next = data->carriages;
	}
	data->carriages = new;
	data->vm.nb_carriages++;
}

static int8_t		do_fork(t_carriages *current, t_data *data,
						enum e_type type)
{
	int16_t		arg;
	t_carriages	*new;

	arg = (int16_t)get_arg(current, data,
				START_ARG | NO_OCP | SMALL_DIR | DIR_FLAG | IND_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	if (type == OP_FORK)
		arg %= IDX_MOD;
	new = get_new_carriage(current, get_pos(current->position + arg),
			data->carriages == NULL ? 0 : data->carriages->id + 1);
	if (new == NULL)
		return (FAILURE);
	add_carriage(new, data);
	return (SUCCESS);
}

/*
**** FORK 0x0c
*/

int8_t				ope_fork(t_carriages *current, t_data *data)
{
	return (do_fork(current, data, OP_FORK));
}

/*
**** FORK 0x0f
*/

int8_t				ope_lfork(t_carriages *current, t_data *data)
{
	return (do_fork(current, data, OP_LFORK));
}
