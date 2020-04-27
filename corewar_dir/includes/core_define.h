/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:16:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/26 14:54:51 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DEFINE_H
# define CORE_DEFINE_H

/*
**		------------------------------ Autres
*/

# define NATURAL_ORDER		0
# define DATA				NULL
# define ONE_LINE			64

/*
**		------------------------------ Gestion d'erreurs
*/

# define ERROR_NB			13
# define PRINT_ERROR		5

# define NO_ERROR_MSG		NULL

# define ER_FILE			1
# define ER_FILE_MSG		"joindre entre un et MAX_PLAYERS fichier .cor\n"

# define ER_DUMP 			2
# define ER_DUMP_MSG		"./corewar [-dump] [0 - INT_MAX] .cor\n"

# define ER_N_USAGE			3
# define ER_N_USAGE_MSG		"./corewar [-n] [0 - MAX_PLAYERS] .cor\n"

# define ER_STDCLOSED		4
# define ER_STDCLOSED_MSG	"sortie standard fermée\n"

# define ER_NAME			5
# define ER_NAME_MSG		"name non-valide\n"

# define ER_NULL 			6
# define ER_NULL_MSG		"4 octets nulls requis\n"

# define ER_SMALL			7
# define ER_SMALL_MSG		"fichier .cor trop court\n"

# define ER_BIG 			8
# define ER_BIG_MSG			"la taille du code executable n'est pas valable\n"

# define ER_MAGIC 			9
# define ER_MAGIC_MSG		"mauvais magic number\n"

# define ER_DIFF			10
# define ER_DIFF_MSG		"la taille du code ne correspond pas\n"

# define ER_SIZE_COMM		11
# define ER_SIZE_COMM_MSG	"la taille du commentaire n'est pas valide\n"

# define ER_INIT			12
# define ER_INIT_MSG		"pas de champion\n"

/*
**		------------------------------ Gestion d'erreurs sans messages
*/

# define NO_ERROR			0
# define ER_OPEN			100
# define ER_READ			101
# define ER_MALLOC			102
# define ER_CLOSE			103

/*
**		------------------------------ OCP
*/

# define GET				0x01
# define SET				0x02
# define BAD_REG			0x08

# define NO_NEED			0x0000
# define IND_LLD			0x0001
# define IND				0x0002
# define SMALL_DIR			0x0004
# define BIG_DIR			0x0008
# define NO_OCP				0x0010
# define REG_NUM			0x0020
# define IND_NUM			0x0040

# define BAD_REG_NB			0x0080
# define REG_FLAG			0x0100
# define DIR_FLAG			0x0200
# define IND_FLAG			0x0300

# define START_ARG			0x4000
# define END_ARG			0x8000

# define T_REG				1
# define T_DIR				2
# define T_IND				3

# define MASK_REG			0x01
# define MASK_DIR			0x02
# define MASK_IND			0x04

# define MASK_LIVE			0x0002
# define MASK_LD			0x0016
# define MASK_ST			0x0051
# define MASK_ADD			0x0111
# define MASK_SUB			0x0111
# define MASK_AND			0x0177
# define MASK_OR			0x0177
# define MASK_XOR			0x0177
# define MASK_ZJMP			0x0002
# define MASK_LDI			0x0137
# define MASK_STI			0x0371
# define MASK_FORK			0x0002
# define MASK_LLD			0x0016
# define MASK_LLDI			0x0137
# define MASK_LFORK			0x0002
# define MASK_AFF			0x0001

# define DIR_			128
# define REG_			64

# define REG_REG_		80
# define REG_IND_		112

/*
** 			----------------------- TYPE_SIZE
*/

# define MEM_DIR		4
# define MEM_SMALL_DIR	2
# define MEM_IND		2
# define MEM_REG		1
# define MEM_OCP		1
# define MEM_OP_CODE	1

/*
** 			----------------------- CARRY
*/

# define CARRY_ON		1
# define CARRY_OFF		0

/*
** 			----------------------- DUMP || AFF
*/

# define OFF			-1
# define ON				0
# define DONE			-2

#endif
