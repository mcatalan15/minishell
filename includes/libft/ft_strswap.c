/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:14:07 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/27 18:40:58 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strswap(char *dst, char *src, char *sub)
{
	char	*tmp;
	char	*aux;
	int		i;
	int		len;

	i = 0;
	aux = ft_strnstr(dst, src, 0x7fffffff);
	if (!aux)
		return (NULL);
	len = ft_strlen(dst) + ft_strlen(sub) - ft_strlen(src);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	len = 0;
	while (dst[i] && dst != aux)
		tmp[i++] = *(dst++);
	dst += ft_strlen(src);
	while (sub[len])
		tmp[i++] = sub[len++];
	while (*dst)
		tmp[i++] = *(dst++);
	tmp[i] = '\0';
	return (tmp);
}

// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;
// 	char	*sub;
// 	char	*result;

// 	str1 = "This is a sample string";
// 	str2 = "sample";
// 	sub = "a long replacement";
// 	printf("Original String: %s\n", str1);
// 	// Call ft_strswap to swap "sample" with "replacement"
// 	result = ft_strswap(str1, str2, sub);
// 	if (result != NULL)
// 	{
// 		printf("After Swap: %s\n", result);
// 		// Don't forget to free the allocated memory when you're done with it
// 		free(result);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failure.\n");
// 	}

// 	return (0);
// }
