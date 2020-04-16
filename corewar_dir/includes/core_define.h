/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:16:31 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/16 16:03:14 by ffoissey         ###   ########.fr       */
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

# define ERROR_NB 13

# define ER_FILE 0
# define ERROR_MSG0 "Usage : joindre un fichier .cor a l'executable\n"

# define ER_MALLOC 1
# define ERROR_MSG1 "Erreur de Malloc\n"

# define ER_N_USAGE 2
# define ERROR_MSG2 "Usage : ./corewar [-n] [0 - MAX_PLAYERS] .cor\n"

# define ER_MAGIC 3
# define ERROR_MSG3 " : mauvais magic number\n"

# define ER_NAME 4
# define ERROR_MSG4 " : name non-valide\n"

# define ER_NULL 5
# define ERROR_MSG5 " : 4 octets nulls requis\n"

# define ER_SMALL 6
# define ERROR_MSG6	" : fichier .cor trop court\n"

# define ER_BIG 7
# define ERROR_MSG7	" : la taille du code executable n'est pas valable\n"

# define ER_STDCLOSED 8
# define ERROR_MSG8 "Erreur : sortie standard fermée\n"

# define ER_DUMP 9
# define ERROR_MSG9 "Usage : ./corewar [-dump] [0 - INT_MAX] .cor\n"

# define ER_READ 10
# define ERROR_MSG10 "Erreur lors de l'utilisation de la fonction READ\n"

# define ER_DIFF 11
# define ERROR_MSG11 "La taille du code executable est différente de la taille donnée par EXEC_CCODE_SIZE\n"

# define ER_SIZE_COMM 12
# define ERROR_MSG12 "La taille du commentaire n'est pas valide\n"

/*
**		------------------------------ OCP
*/

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
