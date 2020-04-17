/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:11:59 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 13:01:35 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_carriages	*get_new_carriage(t_carriages *current, int16_t position,
									int32_t id)
{
	t_carriages		*new;
	uint8_t			nb_reg;

	new = (t_carriages *)ft_memalloc(sizeof(t_carriages));
	if (new != NULL)
	{
		new->position = get_pos(position);
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


static int8_t		do_fork(t_carriages *current, t_data *data, uint16_t flag)
{
	int16_t		arg;
	t_carriages	*new;

	arg = get_arg(current, data, 1, NO_OCP | SMALL_DIR | DIR_FLAG);
	arg = (flag == IDX_MOD) ? get_pos(arg) % IDX_MOD : get_pos(arg);
	new = get_new_carriage(current, get_pos(current->position) + arg,
			data->carriages == NULL ? 0 : data->carriages->id + 1);
	if (new == NULL)
		return (FAILURE); // exit malloc
	add_carriage(new, data);
	return (SUCCESS);
}

/*
**** FORK 0x0c
*/

int8_t			ope_fork(t_carriages *current, t_data *data)
{
	return (do_fork(current, data, IDX_MOD));
}

/*
**** FORK 0x0f
*/

int8_t			ope_lfork(t_carriages *current, t_data *data)
{
	return (do_fork(current, data, NO_NEED));
}
