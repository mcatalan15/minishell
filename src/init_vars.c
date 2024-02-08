/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/08 11:07:51 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	init_vars(char *line, t_shell *shell)
{
	shell->command = command_new();
	shell->end_type = 0;
	shell->command->token = put_tokens(shell->command->token, line, shell);
	if (!shell->command->token)
		return (0);
	return (0);
}
