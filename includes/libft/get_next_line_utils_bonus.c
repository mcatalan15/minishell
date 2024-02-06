/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:07:18 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/06 10:52:27 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strjoin modif 4 get lght besides the normal strjoin function

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	l_s1;
	size_t	l_s2;

	l_s1 = 0;
	if (s1 != NULL)
	{
		l_s1 = ft_strl(s1);
	}
	l_s2 = ft_strl(s2);
	str = (char *)malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < l_s1)
		str[i] = s1[i];
	j = -1;
	while (++j < l_s2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

// ft_strl modif 4 error handeling

size_t	ft_strl(char *str)
{
	int	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

// ft_substr modif

char	*ft_substr_gnl(char *s, unsigned int start, size_t l)
{
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strl(s) < start)
	{
		l = 0;
		start = 0;
	}
	else if (ft_strl(s + start) < l)
		l = ft_strl(s + start);
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	strncpy(str, s + start, l);
	str[l] = '\0';
	return (str);
}
