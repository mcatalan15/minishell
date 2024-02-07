/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:51:38 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/07 11:16:55 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_is_interrogant(char *end_type)
{
	int	len;

	len = 0;
	while (end_type[len])
		len++;
	return (end_type);
}

void	remove_quotes(char *str, char f)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != f)
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i + 1])
	{
		str[i] = str[i + 2];
		str[i + 1] = str[i + 2];
		i++;
	}
}

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

int	get_type(char *str)
{
	if (!str[0])
		return (T_NULL);
	if (str[0] == '>' && str[1] != '>')
		return (T_REDIN);
	if (str[0] == '<' && str[1] != '<')
		return (T_REDOUT);
	if (str[0] == '>' && str[1] == '>')
		return (T_DIN);
	if (str[0] == '<' && str[1] == '<')
		return (T_DOUT);
	if (str[0] == '$' && str[1])
		return (T_DOLLAR);
	if (str[0] == '|')
		return (T_PIPE);
	return (T_STR);
}

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
