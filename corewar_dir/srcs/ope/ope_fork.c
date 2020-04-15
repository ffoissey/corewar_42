/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:16:04 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 19:38:19 by ffoissey         ###   ########.fr       */
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
	while (nb_registre < 16)
	{
		new->registres[nb_registre] = current->registres[nb_registre];
		nb_registre++;
	}
	new->carry = current->carry;
	new->last_live_cycle = current->last_live_cycle;
	return (SUCCESS);
}

int8_t			ope_fork(t_carriages *current, t_data *data)
{
	int16_t		arg;

	current->to_jump = MEM_OP_CODE;
	arg = core_get_small_dir(data,
		(current->position + current->to_jump) % MEM_SIZE);
	current->to_jump += MEM_SMALL_DIR;
	if (get_new_carriage(current, data) == FAILURE)
		return (FAILURE);
	data->carriages->position =
		(current->position + (arg % IDX_MOD)) % MEM_SIZE;
	data->vm.nb_carriages++;
	return (SUCCESS);
}
