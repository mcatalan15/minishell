/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:09:49 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/25 21:15:17 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpc(const char *s1, const char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]) && s1[i + 1] != c)
		i++;
	return (s1[i] - s2[i]);
}
