/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:22:10 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/15 10:35:28 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function checks if the given string is enclosed by quotes. It does so
	by comparing the quote character. It returns 0 if the string is closed and
	1 if it is not.
*/

int	ft_quoted_closed(char *str)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !quote)
			quote = str[i];
		else if (str[i] == '\"' && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
	}
	if (!quote)
		return (0);
	return (1);
}

/*
	This function removes the quotes from the string. It iterates through the
	string and removes the quotes until the character 'f' is found. Then, it
	returns the length of the string without the quotes.
*/

int	remove_quotes(char *str, char f)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i + 1] != f)
	{
		str[i] = str[i + 1];
		i++;
		len++;
	}
	while (str[i + 1])
	{
		str[i] = str[i + 2];
		str[i + 1] = str[i + 2];
		i++;
	}
	return (len);
}

/*
	This function iterates through the string until the first quote is found.
	Then, it removes the quotes from the string and returns the length of the
	modified string.
*/

void	kill_all_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += remove_quotes(&str[i], str[i]) - 1;
	}
}
