# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 10:48:43 by cde-moul          #+#    #+#              #
#    Updated: 2020/03/11 19:22:30 by cde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#																			   #
#								   Targets									   #
#																			   #
#------------------------------------------------------------------------------#

NAME		=		../corewar

LIBFT		=		libft.a

SRCS		+=		$(CORE_FUNCTIONS)
SRCS		+=		$(READ)
SRCS		+=		$(INIT)
SRCS		+=		$(PRESENT)
SRCS		+=		$(OPE)
SRCS		+=		$(GET_ARGS)
SRCS		+=		$(OPE_LIB)
SRCS		+=		$(PUT)
SRCS		+=		$(ERROR)
SRCS		+=		$(FREE)
SRCS		+=		$(PRINT)

OBJS		=		$(patsubst %.c, $(OPATH)%.o, $(SRCS))

LIB			=		$(addprefix $(LPATH), $(LIBFT))

#------------------------------------------------------------------------------#
#																			   #
#								   Directories								   #
#																			   #
#------------------------------------------------------------------------------#

LPATH		=		../libft/
OPATH		=		objs/

IPATH		+=		includes
IPATH		+=		../libft/includes

P_CORE		+=		./
P_CORE		+=		./core_functions/
P_CORE		+=		./read/
P_CORE		+=		./present/
P_CORE		+=		./init/
P_CORE		+=		./ope/
P_CORE		+=		./get_args/
P_CORE		+=		./ope_lib/
P_CORE		+=		./error/
P_CORE		+=		./free/
P_CORE		+=		./print_debug/

_SPATH		+=		$(P_CORE)

SPATH		=		$(addprefix srcs/, $(_SPATH))

#------------------------------------------------------------------------------#
#																			   #
#								   	  Vpath									   #
#																			   #
#------------------------------------------------------------------------------#

vpath %.c $(SPATH)
vpath %.h $(IPATH)

#------------------------------------------------------------------------------#
#																			   #
#						Compiler and compilation flags						   #
#																			   #
#------------------------------------------------------------------------------#

CC			=		clang
LINK		=		$(CC) -g3
COMPILE		=		$(CC) -c -g3

IFLAGS		=		$(addprefix -I , $(IPATH))
CFLAGS		+=		-Wall
CFLAGS		+=		-Wextra
CFLAGS		+=		-Werror
#CFLAGS		+=		-fsanitize=address
# CFLAGS		+=		-Wpadded
CFLAGS		+=		$(IFLAGS)

#------------------------------------------------------------------------------#
#																			   #
#								   Commands									   #
#																			   #
#------------------------------------------------------------------------------#

MKDIR		=		mkdir -p
CLEANUP		=		rm -rf
CLEAR		=		clear
TOUCH		=		touch

#------------------------------------------------------------------------------#
#																			   #
#								    Includes								   #
#																			   #
#------------------------------------------------------------------------------#

INCS		+=		core.h
INCS		+=		op.h
INCS		+=		core_define.h
INCS		+=		core_struct.h

#------------------------------------------------------------------------------#
#																			   #
#								    Sources									   #
#																			   #
#------------------------------------------------------------------------------#

#										   --- Fonctions principales ---

CORE_FUNCTIONS	+=		main.c
CORE_FUNCTIONS	+=		core_cycle.c
CORE_FUNCTIONS	+=		core_check.c

#											 --- Lecture des .cor ---

READ			+=		core_read.c
READ			+=		core_read_functions.c

#										  --- Initialisation des structs ---

INIT			+=		core_init.c
INIT			+=		core_init_flags.c
INIT			+=		core_init_vm.c
INIT			+=		core_init_carriages.c

#										  --- Presentation des champions ---

PRESENT			+=		core_present_champs.c
PRESENT			+=		core_present_winner.c

#												   --- Operations ---

OPE				+=		ope_live.c
OPE				+=		ope_ld.c
OPE				+=		ope_st.c
OPE				+=		ope_add.c
OPE				+=		ope_sub.c
OPE				+=		ope_and.c
OPE				+=		ope_or.c
OPE				+=		ope_xor.c
OPE				+=		ope_zjmp.c
OPE				+=		ope_ldi.c
OPE				+=		ope_sti.c
OPE				+=		ope_fork.c
OPE				+=		ope_lld.c
OPE				+=		ope_lldi.c
OPE				+=		ope_lfork.c
OPE				+=		ope_aff.c

#										  --- Fonctions utiles aux operations ---

OPE_LIB			+=		core_put_reg_ind.c
OPE_LIB			+=		ft_isanint.c

#									  	  --- Recuperation des arguments ---

GET_ARGS		+=		core_get_dir.c
GET_ARGS		+=		core_get_ind.c
GET_ARGS		+=		core_ind_value.c
GET_ARGS		+=		core_ind_value_lld.c
GET_ARGS		+=		core_get_reg.c
GET_ARGS		+=		core_get_ocp.c
GET_ARGS		+=		core_get_small_dir.c

#  											 --- Gestion d'erreurs  ---

ERROR			+=		core_error.c

#								 			  --- Free de Data ---

FREE			+=		core_free.c

#											  --- Print de Data ---

PRINT			+=		core_print.c
PRINT			+=		core_print_carriages.c

#------------------------------------------------------------------------------#
#																			   #
#								    Print									   #
#																			   #
#------------------------------------------------------------------------------#

#												--- Colors ---

GREEN		=		\033[0;32m
RED			=		\033[0;31m
RESET		=		\033[0m
ONELINE		=		\e[1A\r

#												---	Status ---

BIN_STR		=		Binary
DEL_STR		=		Deleted
CREA_STR	=		Created
COM_STR		=		Compiled

#------------------------------------------------------------------------------#
#																			   #
#								    Rules									   #
#																			   #
#------------------------------------------------------------------------------#

all			:		$(NAME)

run			:		$(NAME)
						./$<

$(NAME)		:		$(LIB) $(OPATH) $(OBJS)
					$(LINK)	$(OBJS)	$(CFLAGS) $(LIB) -o $@
					printf "%-20b%-60b%b" "$(NAME):" "$(GREEN)$(BIN_STR)" "$(COM_STR)$(RESET)\n"


$(OBJS)		:		$(OPATH)%.o : %.c $(INCS) Makefile
					$(COMPILE) $(CFLAGS) $< -o $@
					printf "%-20b%-60b%b" "$(NAME):" "$(GREEN)$@" "$(CREA_STR)$(RESET)\n"

$(LIB)		:		FORCE
					$(MAKE) -C $(LPATH)


$(OPATH)	:
					$(MKDIR) $(OPATH)
					printf "%-20b%-60b%b" "$(NAME):" "$(GREEN)$(OPATH)" "$(CREA_STR)$(RESET)\n"

clean		:
					$(MAKE) -C $(LPATH) clean
					$(CLEANUP) $(OPATH)
					printf "%-20b%-60b%b" "$(NAME):" "$(RED)$(OPATH)" "$(DEL_STR)$(RESET)\n"	
					$(CLEANUP) $(NAME).dSYM

fclean		:
					$(MAKE) -C $(LPATH) fclean
					$(CLEANUP) $(OPATH)
					printf "%-20b%-60b%b" "corewar:" "$(RED)$(OPATH)" "$(DEL_STR)$(RESET)\n"	
					$(CLEANUP) $(NAME).dSYM
					$(CLEANUP) $(NAME)
					printf "%-20b%-60b%b" "corewar:" "$(RED)corewar" "$(DEL_STR)$(RESET)\n"	

re			:		fclean
					$(MAKE)

FORCE		:

.PHONY		:		all clean fclean re FORCE

.SILENT:
