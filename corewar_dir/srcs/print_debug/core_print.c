/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:48:25 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 17:04:04 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static uint8_t core_check_pos(t_data *data, int i)
{
	t_carriages *current;

	current = data->carriages;
	while (current)
	{
		if (current->position == i)
			return (TRUE);	
		current = current->next;
	}
	return (FALSE);
}

void		print_data(t_data *data)
{
	int	i;
	int	a;
	int	check_pos;
	t_champs *champs;

	i = 0;
	ft_printf("Il y a %d champion(s)\n", data->initialised_players);
	while (i < 4)
	{
		if (data->champs[i])
		{
			champs = data->champs[i];
			ft_printf("\033[0;32m==================  CHAMP N*%d ==================\033[0m\n", champs->nb_player);
			if (champs->name[0])
				ft_printf("NAME : %s\n", champs->name);
			if (champs->file_path)
				ft_printf("FILE_PATH : %s\n", champs->file_path);
			if (champs->comment[0])
				ft_printf("COMMENT : %s\n", champs->comment);
			if (champs->exec_code_size)
				ft_printf("SIZE : %d\n", champs->exec_code_size);
			//if (champs->exec_code)
			//	ft_printf("EXEC_CODE : %s\n", champs->exec_code);
			ft_printf("NB_PLAYER : %d\n", champs->nb_player);
			ft_printf("COPY_START : %d\n", champs->copy_start);
		}
		i++;
	}
	i = -1;
	a = 0;
	while (++i < MEM_SIZE)
	{
		check_pos = core_check_pos(data, i);
		if (a <= 0)
		{
			if (data->champs[0] && i == data->champs[0]->copy_start)
				a = data->champs[0]->exec_code_size;
			else if (data->champs[1] && i == data->champs[1]->copy_start)
				a = data->champs[1]->exec_code_size;
			else if (data->champs[2] && i == data->champs[2]->copy_start)
				a = data->champs[2]->exec_code_size;
			else if (data->champs[3] && i == data->champs[3]->copy_start)
				a = data->champs[3]->exec_code_size;
		}
		if (check_pos == TRUE)
		{
			if (data->vm->arena[i])
				ft_printf("\033[1;34m%02x\033[0m", data->vm->arena[i]);
			else
				ft_printf("\033[1;34m00\0[0m");	
		}
		else if (a > 0)
		{
			if (data->vm->arena[i])
				ft_printf("\033[0;33m%02x\033[0m", data->vm->arena[i]);
			else
				ft_printf("\033[0;33m00\0[0m");
		}
		else
		{
			if (data->vm->arena[i])
				ft_printf("\033[0;31m%02x\033[0m", data->vm->arena[i]);
			else
				ft_printf("\033[0m00\033[0m");
		}
		if (i > 0 && ((i + 1) % 64  == 0))
			ft_printf("\n");
		else
			ft_printf(" ");
		a--;
	}
}
