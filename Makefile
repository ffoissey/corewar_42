# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/11 17:23:00 by ffoissey          #+#    #+#              #
#    Updated: 2020/04/15 15:05:30 by ffoissey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
################################                ################################
################################ MAIN VARIABLES ################################
################################                ################################
################################################################################

# Name
ASM = ./asm
COREWAR = ./corewar

ASM_DIR = ./asm_dir
COREWAR_DIR = ./corewar_dir

all: $(ASM) $(COREWAR)

$(ASM): FORCE
	$(MAKE) -C $(ASM_DIR)

$(COREWAR): FORCE
	$(MAKE) -C $(COREWAR_DIR)

clean:
	$(MAKE) clean -C $(ASM_DIR)
	$(MAKE) clean -C $(COREWAR_DIR)

fclean:
	$(MAKE) fclean -C $(ASM_DIR)
	$(MAKE) fclean -C $(COREWAR_DIR)

re:
	$(MAKE) re -C $(ASM_DIR)
	$(MAKE) re -C $(COREWAR_DIR)

FORCE:

#----------------------------------- Special ----------------------------------#

.PHONY: clean fclean re all FORCE
