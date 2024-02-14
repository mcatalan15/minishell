/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpnks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:59:03 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 11:31:20 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpnks(char *s1, char *s2)
{
	char	*s1_c;
	char	*s2_c;
	int		i;
	int		result;

	s2_c = strdup(s2);
	s1_c = strdup(s1);
	if (s1_c == NULL || s2_c == NULL)
		return (-1);
	i = -1;
	while (s1_c[++i])
		s1_c[i] = ft_tolower(s1_c[i]);
	i = -1;
	while (s2_c[++i])
		s2_c[i] = ft_tolower(s2_c[i]);
	result = ft_strcmp(s1_c, s2_c);
	free(s1_c);
	free(s2_c);
	return (result);
}
