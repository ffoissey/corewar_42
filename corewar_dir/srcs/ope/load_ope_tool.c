/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ope_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:37:27 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/19 18:42:14 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t	load_value(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[2];
	int32_t		reg_val;
	uint8_t		flag_reg;
	int16_t		pos;
	uint8_t		ocp;

	current->carry = CARRY_OFF;
	ocp = core_get_ocp(data, current->position + 1);
	arg[0] = get_arg(current, data,
			START_ARG | IND_NUM | BIG_DIR, &type);
	if (type == NO_OP)
		return (FAILURE);
	if (((ocp >> 6) & 0x03) == T_IND)
	{
		pos = get_pos(arg[0]);
		if (type == OP_LD)
			pos %= IDX_MOD;
		arg[0] = get_ind_value(data, current->position, arg[0], IND);
	}
	arg[1] = get_arg(current, data, END_ARG | REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	flag_reg = SET | GET;
	reg_val = set_reg_value(current, arg[1], arg[0], &flag_reg);
	if (flag_reg != BAD_REG && reg_val == 0)
		current->carry = CARRY_ON;
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}

int8_t	load_indvalue(t_carriages *current, t_data *data, enum e_type type)
{
	int32_t		arg[3];
	uint8_t		flag_reg;
	int16_t		pos;
	int32_t		to_load;

	flag_reg = (type == OP_LLDI) ? IND : IND_LLD;
	arg[0] = get_arg(current, data, START_ARG | SMALL_DIR | flag_reg, &type);
	if (type == NO_OP)
		return (FAILURE);
	arg[1] = get_arg(current, data, SMALL_DIR, &type);
	arg[2] = get_arg(current, data, END_ARG | REG_NUM, &type);
	if (type == NO_OP)
		return (FAILURE);
	pos = get_pos((arg[0] + arg[1]));
	if (type == OP_LDI)
		pos %= IDX_MOD;
	to_load = get_ind_value(data, current->position, pos, IND);
	flag_reg = SET;
	set_reg_value(current, arg[2], to_load, &flag_reg);
//	ft_printf("ARG[0] = %d, ARG[1] = %d, ARG[2] = %d\n", arg[0], arg[1], arg[2]);
//	for (int i = 0; i < 4; i++) 
//		ft_printf("pos = %d, value: %hhx\n", pos, data->vm.arena[i + pos + current->position]);
//	for (int i = 0; i < REG_NUMBER; i++) 
//		ft_printf("r%d = %x\n", i + 1, current->registres[i]);
//	exit(0);
	return (flag_reg == BAD_REG ? FAILURE : SUCCESS);
}
