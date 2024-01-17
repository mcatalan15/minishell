/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:47:34 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/16 12:12:43 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **ft_split_shell(const char *str)
{
	int i;
	int j;
	int k;
	int count;
	char **arr;

	i = 0;
	j = 0;
	count = 0;
	arr = malloc(sizeof(char *) * 100);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] == '|')
		{
			arr[count] = malloc(sizeof(char) * (i - j + 1));
			k = 0;
			while (j < i)
			{
				arr[count][k] = str[j];
				j++;
				k++;
			}
			arr[count][k] = '\0';
			count++;
			j = i + 1;
		}
		i++;
	}
	arr[count] = malloc(sizeof(char) * (i - j + 1));
	k = 0;
	while (j < i)
	{
		arr[count][k] = str[j];
		j++;
		k++;
	}
	arr[count][k] = '\0';
	count++;
	arr[count] = NULL;
	return (arr);
}
