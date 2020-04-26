/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 10:15:37 by ffoissey          #+#    #+#             */
/*   Updated: 2020/04/26 14:29:11 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	debug_info_champs(t_champs **champs)
{
	uint8_t	i;
	uint8_t	first;

	i = 0;
	first = TRUE;
	while (i < MAX_PLAYERS)
	{
		if (champs[i] != NULL)
		{
			if (i != FALSE)
				ft_dprintf(STDERR_FILENO,
					"------------------------------------------------------\n");
			ft_dprintf(STDERR_FILENO, "nb player\t\t=> %d\nname\t\t\t=> %s\n",
										champs[i]->nb_player, champs[i]->name);
			ft_dprintf(STDERR_FILENO, "comment\t\t\t=> %s\n",
										champs[i]->comment);
			ft_dprintf(STDERR_FILENO, "code size\t\t=> %d\n",
										champs[i]->exec_code_size);
			ft_dprintf(STDERR_FILENO, "last alive cycle\t=> %d\n",
										champs[i]->last_alive_cycle);
			first = FALSE;
		}
		i++;
	}
}

static void	debug_info_carriages(t_carriages *car)
{
	uint8_t	i;

	while (car != NULL)
	{
		ft_dprintf(STDERR_FILENO, "id\t\t\t=> %d\n", car->id);
		ft_dprintf(STDERR_FILENO, "last live cycle\t\t=> %d\n",
									car->last_live_cycle);
		ft_dprintf(STDERR_FILENO, "current pos\t\t=> 0x%.4x | %-6d(decimal)\n",
									car->position, car->position);
		ft_dprintf(STDERR_FILENO, "carry\t\t\t=> %s\n",
									car->carry ? "ON" : "OFF");
		ft_dprintf(STDERR_FILENO, "\nRegistres: ");
		i = 0;
		while (i < REG_NUMBER)
		{
			ft_dprintf(STDERR_FILENO, "%sreg %2d  => %-11d\n",
									i == 0 ? "\t" : "\t\t",
									i + 1, car->registres[i]);
			i++;
		}
		if (car->next != NULL)
			ft_dprintf(STDERR_FILENO,
					"------------------------------------------------------\n");
		car = car->next;
	}
}

void		debug_info(t_data *data)
{
	ft_dprintf(STDERR_FILENO,
			"\n\n#################### INFORMATION ####################\n\n");
	ft_dprintf(STDERR_FILENO,
			"- number of players\t=> %d\n", data->initialised_players);
	ft_dprintf(STDERR_FILENO,
			"- current cycle\t\t=> %d\n", data->vm.nb_cycles);
	ft_dprintf(STDERR_FILENO,
			"- cycle to die\t\t=> %d\n", data->vm.cycles_to_die);
	ft_dprintf(STDERR_FILENO,
			"\n- - - - - - - - - - -  CHAMPS - - - - - - - - - - - - -\n\n");
	debug_info_champs(data->champs);
	ft_dprintf(STDERR_FILENO,
			"\n- - - - - - - - - - - CARRIAGES - - - - - - - - - - - -\n\n");
	debug_info_carriages(data->carriages);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void		debug_opinfo(void)
{
	uint8_t		i;
	const char	*op_str[] = {"\n\nCODE NAME   OCP       ARG1         ",
							"ARG2          ARG3        DIR   CAR\n",
	"-----------------------------------------------------------------------\n",
	"0x01 live        [    DIR    ]                             |  4  |  N |\n",
	"0x02 ld    [OCP] [  DIR/IND  ] [    REG    ]               |  4  |  Y |\n",
	"0x03 st    [OCP] [    REG    ] [  REG/DIR  ]               |  4  |  N |\n",
	"0x04 add   [OCP] [    REG    ] [    REG    ] [    REG    ] |  4  |  Y |\n",
	"0x05 sub   [OCP] [    REG    ] [    REG    ] [    REG    ] |  4  |  Y |\n",
	"0x06 and   [OCP] [REG/DIR/IND] [REG/DIR/IND] [    REG    ] |  4  |  Y |\n",
	"0x07 or    [OCP] [REG/DIR/IND] [REG/DIR/IND] [    REG    ] |  4  |  Y |\n",
	"0x08 xor   [OCP] [REG/DIR/IND] [REG/DIR/IND] [    REG    ] |  4  |  Y |\n",
	"0x09 zjmp        [    DIR    ]                             |  2  |  N |\n",
	"0x0a ldi   [OCP] [REG/DIR/IND] [  REG/DIR  ] [    REG    ] |  2  |  Y |\n",
	"0x0b sti   [OCP] [    REG    ] [REG/DIR/IND] [  REG/DIR  ] |  2  |  N |\n",
	"0x0c fork        [    DIR    ]                             |  2  |  N |\n",
	"0x0d lld   [OCP] [  DIR/IND  ] [    REG    ]               |  4  |  N |\n",
	"0x0e lldi  [OCP] [REG/DIR/IND] [  REG/DIR  ]  [   REG    ] |  2  |  Y |\n",
	"0x0f lfork       [    DIR    ]                             |  2  |  N |\n",
	"0x10 aff   [OCP] [    REG    ]                             |  4  |  N |"};

	i = 0;
	while (i < 18)
		ft_dprintf(STDERR_FILENO, "%s", op_str[i++]);
	ft_putendl_fd("\n", STDERR_FILENO);
}

void		debug_help(void)
{
	ft_dprintf(STDERR_FILENO, "CMD LIST:\n");
	ft_dprintf(STDERR_FILENO, "- exit:\t\t\t ==> exit debug mode\n");
	ft_dprintf(STDERR_FILENO, "- goto [nb_cycle]:\t ==> go to a cycle\n");
	ft_dprintf(STDERR_FILENO, "- help:\t\t\t ==> print cmd list\n");
	ft_dprintf(STDERR_FILENO, "- info:\t\t\t ==> print current info\n");
	ft_dprintf(STDERR_FILENO, "- next:\t\t\t ==> go to next cycle\n");
	ft_dprintf(STDERR_FILENO, "- opinfo:\t\t ==> print info about op\n");
	ft_dprintf(STDERR_FILENO, "- print:\t\t ==> print current dump\n");
}
