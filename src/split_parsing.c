/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:47:34 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/17 18:12:35 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	split_flag(const char *str, int i, char flag)
{
	if (str[i] == '\'' && !flag)
		flag = '\'';
	else if (str[i] == '\"' && !flag)
		flag = '\"';
	else if (flag == str[i])
		flag = '\0';
	return (flag);
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
			flag = split_flag(str, i++, flag);
		if (s < i && s != -1)
		{
			while (str[s] == ' ' || str[s] == '\t')
				s++;
			while (str[i] == ' ' || str[i] == '\t')
				i--;
			res[k] = malloc(sizeof(char) * (i - s + 1));
			ft_strncpy(res[k++], &str[s], (i - s));
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
	split = ft_split_shell_3(str, split, i, s);
	return (split);
}
