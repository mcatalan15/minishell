/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:09:49 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/25 13:26:38 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpc(const char *s1, const char *s2, char c)
{
	printf("HOLA\n");
	while (*s1 && (*s1 == *s2) && *s2 != c)
	{
		s1++;
		s2++;
	}
	printf("value: %d", (*(unsigned char *)s1 - *(unsigned char *)s2));
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
