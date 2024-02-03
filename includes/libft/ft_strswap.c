/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:14:07 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/03 12:43:44 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strswap(char *dst, char *src, char *sub)
{
	char	*tmp;
	char	*aux;
	int		i;
	int		len;
	char	*dst_ptr;

	i = 0;
	aux = ft_strnstr(dst, src, 0x7fffffff);
	if (!aux)
		return (NULL);
	len = ft_strlen(dst) + ft_strlen(sub) - ft_strlen(src);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	dst_ptr = dst;
	len = 0;
	while (*dst_ptr && dst_ptr != aux)
		tmp[i++] = *(dst_ptr++);
	dst_ptr += ft_strlen(src);
	while (sub[len])
		tmp[i++] = sub[len++];
	while (*dst_ptr)
		tmp[i++] = *(dst_ptr++);
	tmp[i] = '\0';
	return (tmp);
}

/*
int	main(void)
{
	char	*str1;
	char	*str2;
	char	*sub;
	char	*result;

	str1 = "This is a sample string";
	str2 = "sample";
	sub = "a long replacement";
	printf("Original String: %s\n", str1);
	result = ft_strswap(str1, str2, sub);
	if (result != NULL)
	{
		printf("After Swap: %s\n", result);
		free(result);
	}
	else
	{
		printf("Memory allocation failure.\n");
	}

	return (0);
}
*/