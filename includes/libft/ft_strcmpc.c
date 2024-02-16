/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:09:49 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/16 11:36:37 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	This function compare two strings until an especific char
*/

int	ft_strcmpc(const char *s1, const char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && s1[i] != c)
		i++;
	if (s1[i] == '=' && !s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}
