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

void	core_error(t_data *data, uint8_t error_nbr)
{
	static char		*messages[ERROR_NB] = {ERROR_MSG0, ERROR_MSG1,
					ERROR_MSG2, ERROR_MSG3, ERROR_MSG4,
					ERROR_MSG5, ERROR_MSG6, ERROR_MSG7,
					ERROR_MSG8, ERROR_MSG9, ERROR_MSG10,
					ERROR_MSG11, ERROR_MSG12, ERROR_MSG13,
					ERROR_MSG14};
	if (error_nbr > NO_ERROR && error_nbr < ERROR_NB)
		ft_putstr_fd(messages[error_nbr], STDERR_FILENO);
	core_free_all(data, error_nbr);
}
