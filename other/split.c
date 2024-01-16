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

int main(int argc, char **argv)
{
	// const char *str = "This is a sentence | This is another sentence | \"This is a sentence| inside quotes\" | 'This is a sente|nce inside single quotes'";
	const char *str = "hola | q \"klk|'";
	char	*arr;
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


