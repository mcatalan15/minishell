/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:20:46 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/27 19:21:25 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	too_manyargs(void)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("minishell: exit: too many arguments\n");
	dup2(fd, 1);
	return (1);
}
