/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:16:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/03/11 19:22:13 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_STRUCT_H
# define CORE_STRUCT_H

/*
**	Structure du champion
*/

typedef struct		s_champs
{
	char			*file_path;
	char			name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	uint8_t			nb_player;
	char			pad[1];
	int32_t			exec_code_size;
	int32_t			copy_start;
	int32_t			last_alive_cycle;
}					t_champs;

/*
**	Structure de la VM
*/

typedef struct		s_vm
{
	unsigned char	arena[MEM_SIZE];
	uint8_t			last_alive_champ;
	char			pad[3];
	int32_t			nb_cycles;
	int32_t			nb_lives;
	int32_t			cycle_last_check;
	int32_t			cycles_to_die;
	int32_t			nb_checks;
	int32_t			nb_carriages;
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
	int16_t					position;
	int32_t					to_jump;
	uint8_t					carry;
	char					pad[7];
}					t_carriages;

/*
**	Structure globale
*/

typedef struct		s_data
{
	t_champs		*champs[4];
	t_vm			*vm;
	t_carriages		*carriages;
	uint8_t			initialised_players;
	char			pad[7];
}					t_data;

#endif
