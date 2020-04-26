# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 10:48:43 by cde-moul          #+#    #+#              #
#    Updated: 2020/04/26 14:18:39 by ffoissey         ###   ########.fr        #
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
SRCS		+=		$(PUT)
SRCS		+=		$(ERROR)
SRCS		+=		$(FREE)
SRCS		+=		$(PRINT)
SRCS		+=		$(DEBUG)

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
P_CORE		+=		./error/
P_CORE		+=		./free/
P_CORE		+=		./debug_mode/

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

# Compiler Debug Flags
ifeq ($(d), 0)
	CFLAGS += -g3
else ifeq ($(d), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
else ifeq ($(d), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
else ifeq ($(d), 3)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
else ifeq ($(d), 4)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
	CFLAGS += -Weverything
endif
ifneq ($(err), no)
	CFLAGS += -Werror
endif

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

OPE				+= 		arithmetic_and_binary_ope.c
OPE				+= 		arithmetic_and_binary_ope_tool.c
OPE				+= 		fork_ope.c
OPE 			+= 		load_ope.c
OPE 			+= 		load_ope_tool.c
OPE 			+= 		special_ope.c
OPE 			+= 		store_ope.c
OPE 			+= 		get_args.c
OPE 			+= 		get_args_tools.c
OPE 			+= 		tools.c

#  											 --- Gestion d'erreurs  ---

ERROR			+=		core_error.c

#								 			  --- Free de Data ---

FREE			+=		core_free.c

#								 			  --- Debug Mode ---

DEBUG			+=		debug.c
DEBUG			+=		debug_info.c
DEBUG			+=		debug_get_cmd.c


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
