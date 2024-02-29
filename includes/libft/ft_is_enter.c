/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_enter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:51:14 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/29 11:21:43 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_enter(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (!str)
		return (1);
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			flag = 1;
	}
	if (!ft_strcmp(str, "\0") || flag != 1)
		return (1);
	return (0);
}
