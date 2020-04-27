/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:41:49 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/22 16:28:47 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	core_error(t_data *data, const uint8_t error_nbr)
{
	static char		*messages[ERROR_NB] = {NO_ERROR_MSG, ER_FILE_MSG,
				ER_DUMP_MSG, ER_N_USAGE_MSG, ER_STDCLOSED_MSG,
				ER_NAME_MSG, ER_NULL_MSG, ER_SMALL_MSG,
				ER_BIG_MSG, ER_MAGIC_MSG,
				ER_DIFF_MSG, ER_SIZE_COMM_MSG,
				ER_INIT_MSG};

	if (error_nbr < PRINT_ERROR)
		ft_dprintf(STDERR_FILENO, "\033[1;31mERROR: \033[0m");
	if (error_nbr > NO_ERROR && error_nbr < ERROR_NB)
		ft_putstr_fd(messages[error_nbr], STDERR_FILENO);
	else if (error_nbr > ERROR_NB)
	{
		if (error_nbr == ER_MALLOC)
			ft_dprintf(STDERR_FILENO, "\033[1;31mERROR: \033[0m");
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	core_free_all(data, error_nbr);
}
