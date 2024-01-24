/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/24 11:55:49 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_type(char *str)
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

static t_token	*token_new(char *str, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

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

static t_token	*put_tokens(t_token *token, char *str)
{
	t_token	*aux;
	int		i;
	int		pos;
	int		flag;
	char	f;

	i = 0;
	aux = NULL;
	while (str[i])
	{
		pos = 0;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		flag = get_type(&str[i]);
		if (flag == T_REDIN || flag == T_REDOUT || flag == T_PIPE)
			token = token_new(ft_substr(str, i++, 1), flag);
		else if (flag == T_DIN || flag == T_DOUT)
		{
			token = token_new(ft_substr(str, i, 2), flag);
			i += 2;
		}
		else if (str[i] != ' ' && str[i])
		{
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
			token = token_new(ft_substr(str, i, pos), flag);
		}
		i += pos;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
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
	//ft_print_tokens(token);
	return (aux);
}

int	init_vars(char *line, t_shell *shell)
{
	//char		**split;

	shell->command = command_new();
	//split = ft_split_shell(line);
	shell->command->token = put_tokens(shell->command->token, line);
	if (!shell->command->token)
		return (0);
	return (0);
}

// echo hola > out|pwd
// |
// ft_split_shell
// |
// echo hola > out
// pwd
// NULL