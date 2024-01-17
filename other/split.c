/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:25:40 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/01/16 22:25:41 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char **ft_split_shell(const char *str)
// {
// 	int i;
// 	int j;
// 	int k;
// 	int count;
// 	char **arr;

// 	i = 0;
// 	j = 0;
// 	count = 0;
// 	arr = malloc(sizeof(char *) * 100);
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '\'' && str[i] != '\"')
// 				i++;
// 			i++;
// 		}
// 		if (str[i] == '|')
// 		{
// 			arr[count] = malloc(sizeof(char) * (i - j + 1));
// 			k = 0;
// 			while (j < i)
// 			{
// 				arr[count][k] = str[j];
// 				j++;
// 				k++;
// 			}
// 			arr[count][k] = '\0';
// 			count++;
// 			j = i + 1;
// 		}
// 		i++;
// 	}
// 	arr[count] = malloc(sizeof(char) * (i - j + 1));
// 	k = 0;
// 	while (j < i)
// 	{
// 		arr[count][k] = str[j];
// 		j++;
// 		k++;
// 	}
// 	arr[count][k] = '\0';
// 	count++;
// 	arr[count] = NULL;
// 	return (arr);
// }

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

char	**ft_split_shell(const char *str)
{
	char	**result;
	int commandcount = 0;
	int start = 0;
	int i = 0;
	int	k = 0;
	char flag = '\0';

	while (str[i])
	{
		while (str[i] && str[i] == '|')
			i++;
		if (str[i] && str[i] != '|')
			commandcount++;
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
	flag = '\0';
	result = malloc(sizeof(char *) * (commandcount + 1));
	i = 0;
	while (str[i])
	{
		start = -1;
		while (str[i] && str[i] == '|')
			i++;
		if (str[i] && str[i] != '|')
			start = i;
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
		if (start < i && start != -1)
		{
			result[k] = malloc(sizeof(char) * (i - start + 1));
			ft_strncpy(result[k], &str[start], (i - start));
			k++;
		}
	}
	result[k] = NULL;
	return (result);
}

int main()
{
	const char *str = "This is a sentence | This is another sentence | \"This is a sentence| inside quotes\" | 'This is a sente|nce inside single quotes'";
	// const char *str = "hola | q \"klk|'";
	char	**arr;
	arr = ft_split_shell(str);
	int count = 0;
	
	while (arr[count] != NULL) {
		printf("Sentence %d: %s\n", count + 1, arr[count]);
		free(arr[count]);
		count++;
	}
	free(arr);

	return 0;
}


