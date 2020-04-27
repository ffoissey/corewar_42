/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:16:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/27 10:56:25 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_STRUCT_H
# define CORE_STRUCT_H

/*
**	Structure du champion
*/

typedef struct		s_champs
{
	const char		*file_path;
	char			name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	uint8_t			nb_player;
	char			pad[1];
	int32_t			exec_code_size;
	int32_t			last_alive_cycle;
	int32_t			copy_start;
}					t_champs;

/*
**	Structure de la VM
*/

typedef struct		s_vm
{
	uint32_t		arena[MEM_SIZE];
	int32_t			nb_cycles;
	int32_t			nb_lives;
	int32_t			cycle_last_check;
	int32_t			cycles_to_die;
	int32_t			nb_checks;
	int32_t			nb_carriages;
	uint8_t			last_alive_champ;
	char			pad[7];
}					t_vm;

/*
**	Structure des chariots (carriages / processus)
*/

typedef struct		s_carriages
{
	struct s_carriages		*previous;
	struct s_carriages		*next;
	int32_t					registres[REG_NUMBER];
	int32_t					id;
	int32_t					last_live_cycle;
	int16_t					cycle_needed;
	uint16_t				position;
	int32_t					to_jump;
	uint8_t					carry;
	char					pad[7];
}					t_carriages;

/*
**	Structure globale
*/

typedef struct		s_data
{
	t_champs		*champs[MAX_PLAYERS + 1];
	t_carriages		*carriages;
	t_vm			vm;
	int32_t			dump;
	int8_t			aff;
	int8_t			debug;
	uint8_t			initialised_players;
	char			pad[1];
}					t_data;

enum	e_cmd
{
	NO_CMD,
	GOTO,
	PRINT,
	INFO,
	HELP,
	EXIT,
	NEXT,
	OPINFO,
	CLEAR,
	SAVE,
	DIFF,
	FLUSH
};

typedef struct		s_debug
{
	enum e_cmd	cmd;
	int32_t		next_cycle;
	int32_t		cur_cycle;
	uint8_t		waiting_cmd;
	char		pad[3];
}					t_debug;

enum	e_type
{
	NO_OP,
	OP_LIVE,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF,
};

typedef	int8_t	(*t_ope)(t_carriages *, t_data *);

#endif
