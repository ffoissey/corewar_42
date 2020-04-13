/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_print_carriages.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:20:39 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/06 15:32:19 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		print_carriages(t_data *data)
{
	t_carriages		*current;
	int				i;
	int				reg_nb;

	i = 0;
	current = data->carriages;
	while (current && ++i)
		current = current->next;
	current = data->carriages;
	while (current)
	{
		reg_nb = -1;
		ft_printf("\033[0;36m============== Carriage n* %d ==============\033[0m\n", --i);
		ft_printf("last live cycle : %d\n", current->last_live_cycle);
		ft_printf("cycle needed : %d\n", current->cycle_needed);
		ft_printf("position : %d\n", current->position);
		ft_printf("valeur de la position : %02x\n", data->vm->arena[current->position]);
		ft_printf("to_jump : %d\n", current->to_jump);
		if (current->carry == CARRY_ON)
			ft_printf("carry : \033[0;32mON\033[0m\n");
		else
			ft_printf("carry : \033[0;31mOFF\033[0m\n");
		ft_printf("~~~ details registres ~~~\n");
		ft_printf("\treg_nb\t\treg_value\n");
		while (++reg_nb < 16)
			ft_printf("\t%d\t\t%d\n", reg_nb, current->registres[reg_nb]);
		current = current->next;
		ft_printf("\n\n");
	}
}
