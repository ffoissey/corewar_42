/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:49:28 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/17 17:50:56 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	exec_op_code(int32_t op_code, t_carriages *current,
			t_data *data)
{
	static int8_t	(*ptr_operation[16])(t_carriages *current, t_data *data) =
					{ope_live, ope_ld, ope_st, ope_add, ope_sub, ope_and,
					ope_or, ope_xor, ope_zjmp, ope_ldi, ope_sti, ope_fork,
					ope_lld, ope_lldi, ope_lfork, ope_aff};
	return (ptr_operation[op_code - 1](current, data));
}

static void		get_new_op_code(t_carriages *current, t_data *data)
{
	int32_t			op_code;
	const int16_t	cycle_needed[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25,
										800, 10, 50, 1000, 2};

	op_code = data->vm.arena[current->position];
	if (op_code <= 16 && op_code > 0)
		current->cycle_needed = cycle_needed[op_code - 1] - 1;
	else
		current->position = (current->position + 1) % MEM_SIZE;
}

static void		exec_current_carriage(t_carriages *current, t_data *data)
{
	int32_t		op_code;

	op_code = data->vm.arena[current->position];
	if (current->cycle_needed > 1)
		current->cycle_needed--;
	else if (op_code < 1 || op_code > 16)
		current->position = (current->position + 1) % MEM_SIZE;
	else if (current->cycle_needed == 1)
	{
		if (exec_op_code(op_code, current, data) == FAILURE)
			current->position = (current->position + 1) % MEM_SIZE;
		else
			current->position = (current->position
				+ current->to_jump)
				% MEM_SIZE;
		current->to_jump = 0;
		current->cycle_needed--;
	}
	else
		get_new_op_code(current, data);
}

void			corewar_dump(t_data *data)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", (uint8_t)data->vm.arena[i]);
		if (i > 0 && ((i + 1) % 64 == 0))
			ft_putchar('\n');
		i++;
	}
	data->dump = DONE;
}

void			core_cycle(t_data *data)
{
	t_carriages	*current;

	while (data->carriages != NULL)
	{
		if (data->vm.nb_cycles == data->dump)
		{
			corewar_dump(data);
			break ;
		}
		data->vm.nb_cycles += 1;
		current = data->carriages;
		exec_current_carriage(current, data);
		while (current->next)
		{
			current = current->next;
			exec_current_carriage(current, data);
		}
		if (data->vm.cycle_last_check ==
			data->vm.cycles_to_die
			|| data->vm.cycles_to_die <= 0)
			core_check(data);
		else
			data->vm.cycle_last_check += 1;
	}
}
