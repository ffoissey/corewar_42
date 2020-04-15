/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:44:08 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/14 17:01:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "stdint.h"
# include <errno.h>

# define EXTENSION		".s"
# define EXTENSION_COR	".cor"
# define LEN_EXTENSION	2

# define CONTINUE		2

# define NO_ADD			0
# define ADD_ENDL		1
# define CUT_TIL_DQUOTE	2

# define GET_NAME		1
# define GET_COM		2

# define CHECK_ARG		0
# define END_ARG		1

/*
**************************
**** ERROR MANAGEMENT ****
**************************
*/

# define USAGE			"Usage: ./asm [-a] {file.s}"
# define EXIT_USAGE		1

# define NO_ERR					0x0000000000000000

# define NO_FILE_NAME			0x0000000000000001
# define ERR_NO_FILE_NAME		"No file name"

# define BAD_EXTENSION			0x0000000000000002
# define ERR_BAD_EXTENSION		"Bad extension: need `.s'"

# define BAD_FD					0x0000000000000004
# define ERR_BAD_FD				"Bad file descriptor"

# define WRONG_LABEL_NAME		0x0000000000000008
# define ERR_WRONG_LABEL_NAME	"Wrong Label name"

# define DOUBLE_LABEL			0x0000000000000010
# define ERR_DOUBLE_LABEL		"Label already exists"

# define NUMERIC_VALUE			0x0000000000000020
# define ERR_NUMERIC_VALUE		"Waiting numeric Value"

# define REG_VALUE				0x0000000000000040
# define ERR_REG_VALUE			"Reg value is not between 1 and REG_NUMBER"

# define UNKNOW_TOKEN			0x0000000000000080
# define ERR_UNKNOW_TOKEN		"Syntax error (unknow token)"

# define BAD_TOKEN				0x0000000000000100
# define ERR_BAD_TOKEN			"Syntax error (unexpected token)"

# define BAD_ARG_OP				0x0000000000000200
# define ERR_BAD_ARG_OP			"Bad kind of argument for this operation"

# define UNCLOSED_DQUOTE		0x0000000000000400
# define ERR_UNCLOSED_DQUOTE	"Unclosed double quote"

# define NAME_TOO_LONG			0x0000000000000800
# define ERR_NAME_TOO_LONG		"Champion name too long"

# define COMMENT_TOO_LONG		0x0000000000001000
# define ERR_COMMENT_TOO_LONG	"Champion comment too long"

# define DOUBLE_NAME			0x0000000000002000
# define ERR_DOUBLE_NAME		"Champion name already define"

# define DOUBLE_COMMENT			0x0000000000004000
# define ERR_DOUBLE_COMMENT		"Champion comment already define"

# define MISS_NAME				0x0000000000008000
# define ERR_MISS_NAME			"Miss champion name"

# define MISS_COMMENT			0x0000000000010000
# define ERR_MISS_COMMENT		"Miss champion comment"

# define BAD_PLACE_NAME			0x0000000000020000
# define ERR_BAD_PLACE_NAME		"Champion name must be defined before any op"

# define BAD_PLACE_COMMENT		0x0000000000040000
# define ERR_BAD_PLACE_COMMENT	"Champion comment must be defined before any op"

# define UNKNOW_LABEL			0x0000000000080000
# define ERR_UNKNOW_LABEL		"Unknow label"

# define NO_OPE					0x0000000000100000
# define ERR_NO_OPE				"No op"

# define BAD_NB_ARG				0x0000000000200000
# define ERR_BAD_NB_ARG			"Bad number of arguments for this operation"

# define TOO_BIG_NBR			0x0000000000400000
# define ERR_TOO_BIG_NBR		"Number out of bounds (greater than ULONG_MAX)"

# define WRITE_ERROR			0x0000000000800000
# define ERR_WRITE				"write: "

# define READ_ERROR				0x0000000001000000
# define ERR_READ				"read: "

# define OPEN_ERROR				0x0000000002000000
# define ERR_OPEN				"open: "

# define MALLOC_ERROR			0x0000000004000000
# define ERR_MALLOC				"malloc: "

# define INVALID_OPT			0x0000000008000000
# define ERR_INVALID_OPT		"asm: invalid option -- "

# define TOO_MANY_ARG			0x0000000010000000
# define ERR_TOO_MANY_ARG		"asm: too many arguments"

/*
**** INFO
*/

# define COREWAR_EXEC_MAGIC		0x00ea83f3

# define MAX_LEN_OP				15

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define PROG_NAME_LENGTH		128
# define PROG_COMMENT_LENGTH	2048

/*
**** Argument Setting
*/

# define IND_SIZE	2
# define REG_SIZE	4
# define DIR_SIZE	REG_SIZE

# define MAX_ARG	3

# define T_REG		0x01
# define T_DIR		0x02
# define T_IND		0x04

# define REG_MASK	0x01
# define DIR_MASK	0x02
# define IND_MASK	0x03

# define IS_OP_CODE	0x1000

# define NO_OP_ARG	0x0000
# define LIVE_ARG	0x0002
# define LD_ARG		0x1016
# define ST_ARG		0x1051
# define ADD_ARG	0x1111
# define SUB_ARG	0x1111
# define AND_ARG	0x1177
# define OR_ARG		0x1177
# define XOR_ARG	0x1177
# define ZJMP_ARG	0x0002
# define LDI_ARG	0x1137
# define STI_ARG	0x1371
# define FORK_ARG	0x0002
# define LLD_ARG	0x1016
# define LLDI_ARG	0x1137
# define LFORK_ARG	0x0002
# define AFF_ARG	0x1001

/*
**** special
*/

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define LEN_NAME				5
# define LEN_COM				8

/*
**** separator
*/

# define DELIMITER_CHARS		" \t,#;\""

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

/*
**** opcode
*/

# define LIVE			"live"
# define LD				"ld"
# define ST				"st"
# define ADD			"add"
# define SUB			"sub"
# define AND			"and"
# define OR				"or"
# define XOR			"xor"
# define ZJMP			"zjmp"
# define LDI			"ldi"
# define STI			"sti"
# define FORK			"fork"
# define LLD			"lld"
# define LLDI			"lldi"
# define LFORK			"lfork"
# define AFF			"aff"

# define NB_TOKEN		33
# define NB_TRUE_TOKEN	30
# define NB_OP			16

# define CONTINUE		2
# define DQUOTE			4

# define REG_NUMBER		16

enum	e_token
{
	NO_OP,
	OP_LIVE = 0x01,
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
	CMD_NAME,
	CMD_COMMENT,
	REG,
	INDIRECT_LABEL,
	DIRECT,
	DIRECT_LABEL,
	SEP,
	SPACE_TAB,
	SPACE,
	ENDL,
	COMMENT_HASH,
	COMMENT_SEMICOLON,
	STRING,
	LABEL,
	INDIRECT,
	UNKNOW
};

typedef	struct		s_token
{
	char			*str;
	char			*initial_str;
	size_t			col;
	size_t			line;
	size_t			mem_offset;
	size_t			op_size;
	size_t			arg_size;
	int64_t			value;
	int64_t			truevalue;
	enum e_token	type;
	uint16_t		mask;
	char			pad[2];
}					t_token;

typedef struct		s_asm
{
	char			*name;
	char			*comment;
	char			*cor_file;
	t_vector		*dquote;
	t_vector		*output;
	t_list			*op_ptr;
	char			**grammar;
	ssize_t			len_name;
	ssize_t			len_com;
	uint64_t		error;
	t_token			*token_error;
	size_t			start_col_dquote;
	size_t			start_line_dquote;
	t_list			*label_list;
	t_list			*token_list;
	size_t			mem_count;
	size_t			line;
	size_t			col;
	int				fd;
	uint8_t			a_opt;
	char			pad[3];
}					t_asm;

/*
***	asm.c
*/

t_asm				*get_env_asm(t_asm *env_asm);

/*
*** error.c
*/

void				exit_usage(uint64_t err, char c);
int					print_error(uint64_t err, t_token *token);

/*
*** exit_routine.c
*/

void				exit_error(uint64_t err, t_token *token);
void				exit_routine(void);
void				del_token(void *content, size_t content_size);

/*
*** file.c
*/

void				get_file_fd(t_asm *env_asm, char *name);
void				write_file(t_asm *env_asm, char *name);

/*
*** parser.c
*/

void				parser(t_asm *env_asm);

/*
*** token.c
*/

int					extract_token(enum e_token type, t_vector *elem,
						t_asm *env_asm, const uint8_t flag);

/*
*** debug.c
*/

void				debug(void);

/*
*** operation_checker.c
*/

void				op_checker(t_asm *env_asm);

/*
*** tools.c
*/

int					is_arg_type(enum e_token type);
int					is_label_type(enum e_token type);
int					is_num_type(enum e_token type);
int					check_label(char *label_name);
int					is_label_uniq(t_list *label_list, char *str);

/*
*** tools2.c
*/

void				reset_split(void);
int					is_comment(t_vector *split);
void				reset_col_and_increment_line(t_asm *env_asm);
t_list				*go_to_next_op(t_list *lst);
int					is_op_token(t_token *token);

/*
*** label_attribution.c
*/

void				label_attribution(t_asm *env_asm);

/*
*** name_comment.c
*/

void				get_name_and_comment(t_asm *env_asm);

/*
*** encode.c
*/

uint8_t				*mem_rev(uint8_t *mem, size_t size);
t_vector			*encoding(t_asm *env_asm);
size_t				fill_vector(t_vector *output, char *s, size_t len,
						size_t offset);

/*
*** fill_op.c
*/

void				fill_with_op(t_vector *output, t_asm *env_asm);

#endif
