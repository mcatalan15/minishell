/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:43:19 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/15 12:47:47 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	num_words(const char *str, char delim)
{
	int	i;
	int	followed;
	int	num_words;

	i = 0;
	followed = 0;
	num_words = 0;
	while (str[i])
	{
		if (str[i] != delim && followed == 0)
		{
			num_words++;
			followed = 1;
		}
		else if (str[i] == delim)
			followed = 0;
		i++;
	}
	return (num_words);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*ext_split(char const *str, int s, int f)
{
	int		j;
	char	*arr;

	j = 0;
	arr = malloc(sizeof(char) * (f - s + 1));
	if (!arr)
		return (NULL);
	while (s < f)
	{
		arr[j] = str[s];
		s++;
		j++;
	}
	arr[j] = '\0';
	return (arr);
}

static char	**ft_split_ext(char **arr, char *str, char c)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	j = 0;
	pos = -1;
	while (i <= ft_strlen((char *)str))
	{
		if (str[i] != c && pos == -1)
			pos = i;
		else if ((str[i] == c || i == ft_strlen((char *)str)) && pos != -1)
		{
			arr[j] = ext_split(str, pos, i);
			if (!arr[j++])
			{
				free_arr(arr);
				return (NULL);
			}
			pos = -1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split_shell(char const *str)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (num_words(str, '|') + 1));
	if (!str || !arr)
		return (NULL);
	arr = ft_split_ext(arr, (char *)str, '|');
	
	return (arr);
}
