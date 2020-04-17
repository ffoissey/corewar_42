/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:16:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/17 13:30:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DEFINE_H
# define CORE_DEFINE_H

/*
**		------------------------------ Autres
*/

# define NATURAL_ORDER 0

/*
**		------------------------------ Gestion d'erreurs
*/

# define ERROR_NB 10

# define ERROR_MSG0 "Usage : joindre un fichier .cor a l'executable\n"
# define ERROR_MSG1 "Erreur de Malloc\n"
# define ERROR_MSG2 "Usage : ./corewar [-n] [0 - MAX_PLAYERS] .cor\n"
# define ERROR_MSG3 " : mauvais magic number\n"
# define ERROR_MSG4 " : name non-valide\n"
# define ERROR_MSG5 " : 4 octets nulls requis\n"
# define ERROR_MSG6	" : fichier .cor trop court\n"
# define ERROR_MSG7	" : la taille du code executable n'est pas valable\n"
# define ERROR_MSG8 "Erreur : sortie standard fermée\n"
# define ERROR_MSG9 "Usage : ./corewar [-dump] [0 - INT_MAX] .cor\n"


/*
**		------------------------------ OPE
*/

# define BINARY_AND		0x01
# define BINARY_OR		0x02
# define BINARY_XOR		0x04
# define ARITHMETIC_ADD	0x08
# define ARITHMETIC_SUB	0x10

/*
**		------------------------------ OCP
*/


# define GET			0x01
# define SET			0x02
# define BAD_REG		0x04

# define NO_NEED		0x0000
# define IND_LLD		0x0001
# define IND			0x0002
# define SMALL_DIR		0x0004
# define BIG_DIR		0x0008
# define OCP			0x0010
# define NO_OCP			0x0020
# define REG_FLAG		0x0100
# define DIR_FLAG		0x0200
# define IND_FLAG		0x0300

# define INIT_ARG		0x8000

# define T_REG			1
# define T_DIR			2
# define T_IND			3

# define DIR_			128
# define REG_			64

# define DIR_REG_		144
# define IND_REG_		208
# define REG_REG_		80
# define REG_IND_		112

# define REG_REG_REG_	84
# define REG_DIR_REG_	100
# define REG_IND_REG_	116
# define REG_REG_DIR_	88
# define REG_DIR_DIR_	104
# define REG_IND_DIR_	120

# define DIR_REG_REG_	148
# define DIR_DIR_REG_	164
# define DIR_IND_REG_	180

# define IND_REG_REG_	212
# define IND_DIR_REG_	228
# define IND_IND_REG_	244

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
# define ON			0
# define DONE			-2

#endif
