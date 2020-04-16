/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:43:09 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 17:47:21 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		core_kill(t_carriages *current, t_data *data)
{
	t_carriages *next;
	t_carriages *previous;

	data->vm.nb_carriages--;
	next = current->next;
	previous = current->previous;
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	if (data->carriages == current)
		data->carriages = next;
	free(current);
}

void			core_check(t_data *data)
{
	t_carriages *current;
	t_carriages *next;

	current = data->carriages;
	data->vm.nb_checks += 1;
	data->vm.nb_carriages = 0;
	while (current != NULL)
	{
		next = current->next;
		if (data->vm.nb_cycles - current->last_live_cycle
			>= data->vm.cycles_to_die
			|| data->vm.cycles_to_die <= 0)
			core_kill(current, data);
		current = next;
	}
	if (data->vm.nb_lives >= NBR_LIVE || data->vm.nb_checks >= MAX_CHECKS)
	{
		data->vm.cycles_to_die -= CYCLE_DELTA;
		data->vm.nb_checks = 0;
	}
	data->vm.cycle_last_check = 1;
	data->vm.nb_lives = 0;
}
