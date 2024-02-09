/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpnks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:59:03 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/09 13:05:04 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpnks(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		s1[i] = ft_tolower(s1[i]);
	i = -1;
	while (s2[++i])
		s2[i] = ft_tolower(s2[i]);
	return (ft_strcmp(s1, s2));
}
