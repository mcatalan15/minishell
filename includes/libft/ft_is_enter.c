/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_enter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:51:14 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/03 19:52:00 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_enter(char *str)
{
	int	i;
	int	flag;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			flag = 1;
	}
	if (!ft_strcmp(str, "\0") || flag == 1)
		return (1);
	return (0);
}
