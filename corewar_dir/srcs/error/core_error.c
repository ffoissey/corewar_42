/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:41:49 by cde-moul          #+#    #+#             */
/*   Updated: 2020/04/15 17:40:13 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int8_t		core_error(int8_t error_nbr)
{
	static char		*messages[ERROR_NB] = {ERROR_MSG0, ERROR_MSG1,
					ERROR_MSG2, ERROR_MSG3, ERROR_MSG4,
					ERROR_MSG5, ERROR_MSG6, ERROR_MSG7,
					ERROR_MSG8, ERROR_MSG9, ERROR_MSG10};

	ft_putstr_fd(messages[error_nbr], STDERR_FILENO);
	return (FAILURE);
}
