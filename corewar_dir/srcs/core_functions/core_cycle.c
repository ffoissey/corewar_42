/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:49:28 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/12 12:49:19 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int8_t	exec_op_code(int32_t op_code, t_carriages *current,
			t_data *data)
{
	int8_t	(*ptr_operation[16])(t_carriages *current, t_data *data);

	ptr_operation[0] = ope_live;
	ptr_operation[1] = ope_ld;
	ptr_operation[2] = ope_st;
	ptr_operation[3] = ope_add;
	ptr_operation[4] = ope_sub;
	ptr_operation[5] = ope_and;
	ptr_operation[6] = ope_or;
	ptr_operation[7] = ope_xor;
	ptr_operation[8] = ope_zjmp;
	ptr_operation[9] = ope_ldi;
	ptr_operation[10] = ope_sti;
	ptr_operation[11] = ope_fork;
	ptr_operation[12] = ope_lld;
	ptr_operation[13] = ope_lldi;
	ptr_operation[14] = ope_lfork;
	ptr_operation[15] = ope_aff;
	return (ptr_operation[op_code - 1](current, data));
}

static void		get_new_op_code(t_carriages *current, t_data *data)
{
	int32_t		op_code;
	int16_t		cycle_needed[16];

	cycle_needed[0] = 10;
	cycle_needed[1] = 5;
	cycle_needed[2] = 5;
	cycle_needed[3] = 10;
	cycle_needed[4] = 10;
	cycle_needed[5] = 6;
	cycle_needed[6] = 6;
	cycle_needed[7] = 6;
	cycle_needed[8] = 20;
	cycle_needed[9] = 25;
	cycle_needed[10] = 25;
	cycle_needed[11] = 800;
	cycle_needed[12] = 10;
	cycle_needed[13] = 50;
	cycle_needed[14] = 1000;
	cycle_needed[15] = 2;
	op_code = data->vm->arena[current->position];
	if (op_code <= 16 && op_code > 0)
		current->cycle_needed = cycle_needed[op_code - 1] - 1;
	else
		current->position = (current->position + 1) % MEM_SIZE;
	return ;
}

static void		exec_current_carriage(t_carriages *current, t_data *data)
{
	int32_t		op_code;

	op_code = data->vm->arena[current->position];
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
		current->cycle_needed--;
	}
	else
		get_new_op_code(current, data);
	return ;
}

void			corewar_dump(t_data *data)
{
	int 		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x", data->vm->arena[i]);
		if (i > 0 && ((i + 1) % 64 == 0))
			ft_printf("\n");
		else
			ft_printf(" ");
	}
	// je crois qu'on doit exit si on fait un dump et pas dire qui a won.
}

void			core_cycle(t_data *data)
{
	t_carriages	*current;

	while (data->carriages != NULL)
	{
		if (data->vm->nb_cycles == data->dump)
			corewar_dump(data);
		data->vm->nb_cycles += 1;
		current = data->carriages;
		exec_current_carriage(current, data);
		while (current->next)
		{
			current = current->next;
			exec_current_carriage(current, data);
		}
		if (data->vm->cycle_last_check ==
			data->vm->cycles_to_die
			|| data->vm->cycles_to_die <= 0)
			core_check(data);
		else
			data->vm->cycle_last_check += 1;
	}
	return ;
}
