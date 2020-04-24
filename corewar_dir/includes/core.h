/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:57:01 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/24 17:10:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"
# include "op.h"
# include "core_struct.h"
# include "core_define.h"
# include "fcntl.h"
# include <errno.h>

/*
**		CORE_INIT
*/

int8_t		core_init_data(int ac, char **av, t_data *data);
int32_t		core_init_flag(int32_t ac, char **av, t_data *data);
int8_t		get_player_number(char **av, int32_t *i);

/*
**		CORE_CYCLE
*/

void		core_cycle(t_data *data);
void		core_check(t_data *data);

/*
**		CORE_PRESENT
*/

int8_t		core_present_champs(t_data *data);
int8_t		core_present_winner(t_data *data);

/*
**		CORE_INIT_VM
*/

int8_t		core_init_data_vm(t_data *data);
int8_t		core_install_champ(t_champs *champs,
		int32_t fd, t_data *data, int8_t champ_nb);

/*
**		CORE_READ
*/

int8_t		core_read(t_data *data);

/*
**		CORE_READ_FUNCTIONS
*/

int8_t		core_read_exec_code_size(t_champs *champs, int32_t fd);
int8_t		core_read_comment(t_champs *champs, int32_t fd);
int8_t		core_fd_empty(int32_t fd);

/*
**		CORE_INIT_CARRIAGES
*/

int8_t		core_init_carriages(t_data *data);

/*
**		CORE_ERROR
*/

int8_t		core_error(int8_t error_nbr);

/*
**		CORE_PRINT
*/

void		print_data(t_data *data);
void		print_carriages(t_data *data);

/*
**		CORE_FREE
*/

void		core_free_all(t_data *data);

/*
**		CORE_OPE
*/

int8_t		do_op(t_carriages *current, t_data *data, enum e_type type);
int8_t		load_value(t_carriages *current, t_data *data, enum e_type type);
int8_t		load_indvalue(t_carriages *current, t_data *data, enum e_type type);

int8_t		ope_live(t_carriages *current, t_data *data);
int8_t		ope_ld(t_carriages *current, t_data *data);
int8_t		ope_st(t_carriages *current, t_data *data);
int8_t		ope_add(t_carriages *current, t_data *data);
int8_t		ope_sub(t_carriages *current, t_data *data);
int8_t		ope_and(t_carriages *current, t_data *data);
int8_t		ope_or(t_carriages *current, t_data *data);
int8_t		ope_xor(t_carriages *current, t_data *data);
int8_t		ope_zjmp(t_carriages *current, t_data *data);
int8_t		ope_ldi(t_carriages *current, t_data *data);
int8_t		ope_sti(t_carriages *current, t_data *data);
int8_t		ope_fork(t_carriages *current, t_data *data);
int8_t		ope_lld(t_carriages *current, t_data *data);
int8_t		ope_lldi(t_carriages *current, t_data *data);
int8_t		ope_lfork(t_carriages *current, t_data *data);
int8_t		ope_aff(t_carriages *current, t_data *data);

/*
**		get_args
*/

int32_t		get_arg(t_carriages *current, t_data *data, uint16_t flag,
				enum e_type *type);
/*
**** get_args_tools.c
*/

int32_t		core_get_dir(t_data *data, int16_t position, uint16_t flag);
int32_t		core_get_ind(t_data *data, int16_t position, int16_t to_jump,
				uint16_t flag);
int8_t		core_get_reg(t_data *data, int16_t position, t_carriages *current);
uint8_t		core_get_ocp(t_data *data, int16_t position);

/*
**** tools.c
*/

uint16_t	get_pos(int16_t position);
int32_t		get_ind_value(t_data *data, uint16_t position, int16_t arg,
					uint16_t flag);
int32_t		set_reg_value(t_carriages *current, uint8_t reg, int32_t value,
				uint8_t *flag);

#endif
