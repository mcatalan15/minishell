/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:51:38 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/14 18:31:14 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	This function appends a character to the string and returns the new
	string, freeing the memory of the old string.
*/

char	*addstr(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}

/*
	This function returns the type of the token by examining the first
	character of the string and returning the corresponding type value.
*/

int	get_type(char *str)
{
	if (!str[0])
		return (T_NULL);
	if (str[0] == '<' && str[1] != '<')
		return (T_REDIN);
	if (str[0] == '>' && str[1] != '>')
		return (T_REDOUT);
	if (str[0] == '<' && str[1] == '<')
		return (T_DIN);
	if (str[0] == '>' && str[1] == '>')
		return (T_DOUT);
	if (str[0] == '$' && str[1])
		return (T_DOLLAR);
	if (str[0] == '|')
		return (T_PIPE);
	return (T_STR);
}

/*
	This function creates and initializes a new token, then returns it.
	It allocates memory for the token and sets the values of the string, type,
	shell, next, and prev members.
*/

t_token	*token_new(char *str, int type, t_shell *shell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->shell = shell;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
