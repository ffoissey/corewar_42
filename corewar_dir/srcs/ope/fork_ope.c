/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:11:59 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/17 11:13:46 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	get_new_carriage(t_carriages *current, t_data *data)
{
	t_carriages		*new;
	t_carriages		*last;
	int8_t			nb_registre;

	nb_registre = 0;
	new = (t_carriages *)ft_memalloc(sizeof(t_carriages));
	if (new == NULL)
		return (FAILURE);
	last = data->carriages;
	data->carriages = new;
	new->next = last;
	last->previous = new;
	new->id = last->id + 1;
	while (nb_registre < REG_NUMBER)
	{
		new->registres[nb_registre] = current->registres[nb_registre];
		nb_registre++;
	}
	new->carry = current->carry;
	new->last_live_cycle = current->last_live_cycle;
	return (SUCCESS);
}

/*
**** FORK 0x0c
*/

int8_t			ope_fork(t_carriages *current, t_data *data)
{
	int16_t		arg;

	arg = get_arg(current, data, 1, NO_OCP | SMALL_DIR | DIR_FLAG);
	if (get_new_carriage(current, data) == FAILURE)
		return (FAILURE);
	data->carriages->position = 
		get_pos(get_pos(current->position) + (arg % IDX_MOD));
	data->vm.nb_carriages++;
	return (SUCCESS);
}

/*
**** FORK 0x0f
*/

int8_t			ope_lfork(t_carriages *current, t_data *data)
{
	int16_t		arg;

	arg = get_arg(current, data, 1, NO_OCP | SMALL_DIR | DIR_FLAG);
	if (get_new_carriage(current, data) == FAILURE)
		return (FAILURE);
	data->carriages->position =
		(current->position + arg) % MEM_SIZE;
	data->vm.nb_carriages++;
	return (SUCCESS);
}
