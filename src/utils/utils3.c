/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:51:38 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/15 10:35:31 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/*
	This function, which is the second part of the join_subt function, appends
	the whitespace character to the string and adds the new token to the list
	of tokens.
*/

void	join_subt2(t_token *token, char **str, t_token **new, t_shell *shell)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (!ft_isspace(token->str[i]) || token->type != T_STR)
			*str = addstr(*str, token->str[i]);
		else
		{
			add_new_token(new, str, shell);
			while (ft_isspace(token->str[i + 1]))
				i++;
		}
	}
}
