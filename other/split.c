/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:25:40 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/01/17 12:17:37 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_split_shell_2(const char *str, int i)
{
	char	flag;
	int		cmdc;

	cmdc = 0;
	flag = '\0';
	while (str[i])
	{
		while (str[i] && str[i] == '|')
			i++;
		if (str[i] && str[i] != '|')
			cmdc++;
		while (str[i] && (str[i] != '|' || flag))
		{
			if (str[i] == '\'' && !flag)
				flag = '\'';
			else if (str[i] == '\"' && !flag)
				flag = '\"';
			else if (flag == str[i])
				flag = '\0';
			i++;
		}
	}
	return (cmdc);
}

char	**ft_split_shell_3(const char *str, char **res, int i, int s)
{
	char	flag;
	int		k;

	k = 0;
	flag = '\0';
	while (str[i])
	{
		while (str[i] && str[i] == '|')
			i++;
		if (str[i] && str[i] != '|')
			s = i;
		while (str[i] && (str[i] != '|' || flag))
		{
			if (str[i] == '\'' && !flag)
				flag = '\'';
			else if (str[i] == '\"' && !flag)
				flag = '\"';
			else if (flag == str[i])
				flag = '\0';
			i++;
		}
		if (s < i && s != -1)
		{
			res[k] = malloc(sizeof(char) * (i - s + 1));
			ft_strncpy(res[k], &str[s], (i - s));
			k++;
		}
	}
	res[k] = NULL;
	return (res);
}

char	**ft_split_shell(const char *str)
{
	char	**split;
	int		i;
	int		s;

	i = 0;
	s = -1;
	split = malloc(sizeof(char *) * (ft_split_shell_2(str, i) + 1));
	split = ft_split_shell_3(str, split, i, i);
	// split = ft_rm_spaces(split);
	return (split);
}

int	main()
{
	const char	*str = "This is a sentence | This is another sentence | \"This is a sentence| inside quotes\" | 'This is a sente|nce inside single quotes'";
	// const char *str = "hola | q \"klk|'";
	char	**arr;
	arr = ft_split_shell(str);
	int count = 0;

	while (arr[count] != NULL)
	{
		printf("Sentence %d: %s\n", count + 1, arr[count]);
		free(arr[count]);
		count++;
	}
	free(arr);

	return (0);
}


