/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:49:28 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/24 21:31:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t		exec_op_code(uint32_t op_code, t_carriages *current,
					t_data *data)
{
	static t_ope	ptr_operation[16] = {ope_live, ope_ld, ope_st, ope_add,
					ope_sub, ope_and, ope_or, ope_xor,
					ope_zjmp, ope_ldi, ope_sti, ope_fork,
					ope_lld, ope_lldi, ope_lfork, ope_aff};

	return (ptr_operation[op_code - 1](current, data));
}

static int		get_new_op_code(t_carriages *current, t_data *data)
{
	uint8_t			op_code;
	const int16_t	cycle_needed[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25,
							800, 10, 50, 1000, 2};

	op_code = (uint8_t)data->vm.arena[get_pos(current->position)];
	if (op_code > 16 || op_code <= 0)
		return (FAILURE);
	current->cycle_needed = cycle_needed[op_code - 1] - 1;
	return (SUCCESS);
}

static void		exec_current_carriage(t_carriages *current, t_data *data)
{
	uint8_t		op_code;

	if (current->cycle_needed > 0)
	{
		current->cycle_needed--;
		if (current->cycle_needed == 0)
		{
			op_code = data->vm.arena[get_pos(current->position)];
			if (op_code > 16 || op_code <= 0)	
				current->position = get_pos(current->position + 1);
			else if (exec_op_code(op_code, current, data) == FAILURE)
				current->position = get_pos(current->position + 1);
			else
				current->position = get_pos(current->position + current->to_jump);
			current->to_jump = 0;
		}
	}
	else
	{
		if (get_new_op_code(current, data) == FAILURE)
			current->position = get_pos(current->position + 1);
	}
}

void				corewar_dump(t_data *data)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % ONE_LINE == SUCCESS)
		{
			if (ft_printf("0x%04x : ", i) == FAILURE)
				core_error(data, ER_STDCLOSED);
		}
		if (ft_printf("%02x ", (uint8_t)data->vm.arena[i]) == FAILURE)
			core_error(data, ER_STDCLOSED);
		if (i > 0 && ((i + 1) % ONE_LINE == SUCCESS))
		{
			if (ft_putchar('\n') == FAILURE)
				core_error(data, ER_STDCLOSED);
		}
		i++;
	}
	if (data->debug == OFF)
		core_free_all(data, NO_ERROR);
}

void			core_cycle(t_data *data)
{
	t_carriages	*current;

	while (data->carriages != NULL)
	{
		debug_process(data); //
		current = data->carriages;
		if (data->vm.nb_cycles == data->dump)
		{
			corewar_dump(data);
			break ;
		}
		data->vm.nb_cycles += 1;
		while (current != NULL)
		{
			exec_current_carriage(current, data);
			current = current->next;
		}
		if (data->vm.cycle_last_check ==
			data->vm.cycles_to_die
			|| data->vm.cycles_to_die <= 0)
			core_check(data);
		else
			data->vm.cycle_last_check += 1;
	}
}
