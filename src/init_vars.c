/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/29 10:47:04 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function initializes the command structure.
*/

static t_command	*command_new(void)
{
	t_command	*command_new;

	command_new = malloc(sizeof(t_command));
	if (!command_new)
		return (NULL);
	command_new->cmd = NULL;
	command_new->path = NULL;
	return (command_new);
}

/*
	This function splits the tokens according to the quotes and returns the
	position of the next token.
*/

static int	split_manage(char *str, int i, int pos)
{
	char	f;

	f = '\0';
	while ((!ft_isspace(str[i + pos]) && str[i + pos] && \
	!ft_isoperate(get_type(&str[i + pos]))) || (f && str[i + pos]))
	{
		if (ft_isdquote(str[i + pos]) && !f)
			f = '\"';
		else if (ft_issquote(str[i + pos]) && !f)
			f = '\'';
		else if (str[i + pos] == f)
			f = '\0';
		pos++;
	}
	return (pos);
}

/*
	This function gets the tokens from the input string and splits them
	according to the type of token and the quotes.
	Return the token structure with a pointer to the next token.
*/

static t_token	*get_tokens(t_token *token, char *str, int *i, t_shell *shell)
{
	int	pos;
	int	flag;

	pos = 0;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	flag = get_type(&str[*i]);
	if (flag == T_REDIN || flag == T_REDOUT || flag == T_PIPE)
		token = token_new(ft_substr(str, (*i)++, 1), flag, shell);
	else if (flag == T_DIN || flag == T_DOUT)
	{
		token = token_new(ft_substr(str, *i, 2), flag, shell);
		*i += 2;
	}
	else if (str[*i] != ' ' && str[*i])
	{
		pos = split_manage(str, *i, pos);
		token = token_new(ft_substr(str, *i, pos), flag, shell);
	}
	*i += pos;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	return (token);
}

/*
	This function puts the tokens in a list.
*/

t_token	*put_tokens(t_token *token, char *str, t_shell *shell)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = NULL;
	while (str[i])
	{
		token = get_tokens(token, str, &i, shell);
		token->prev = aux;
		aux = token;
		token = token->next;
	}
	while (aux->prev)
	{
		token = aux;
		aux = aux->prev;
		aux->next = token;
	}
	token = aux;
	return (aux);
}

/*
	This function initializes the variables of the shell.
*/

int	init_vars(char *line, t_shell *shell)
{
	shell->command = command_new();
	shell->command->pid = NULL;
	shell->command->hd = NULL;
	shell->command->token = put_tokens(shell->command->token, line, shell);
	g_signal = 0;

	if (!shell->command->token)
		return (0);
	return (0);
}
