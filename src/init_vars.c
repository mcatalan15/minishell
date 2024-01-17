/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/17 19:54:26 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_type(char *str)
{
	if (!str[0])
		return (0);
	if (ft_isalnum(str[0]))
		return (1);
	if (str[0] == '\"')
		return (2);
	if (str[0] == '\'')
		return (3);
	if (str[0] == '>' && str[1] != '>')
		return (4);
	if (str[0] == '<' && str[1] != '<')
		return (5);
	if (str[0] == '>' && str[1] == '>')
		return (6);
	if (str[0] == '<' && str[1] == '<')
		return (7);
	if (str[0] == '$' && str[1])
		return (8);
	return (0);
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
	command_new->next = NULL;
	command_new->prev = NULL;
	return (command_new);
}

static t_token	*put_tokens(t_token *token, char *str)
{
	t_token	*aux;
	int		i;
	int		pos;
	int		flag;

	// la lista se crea pero aux no apunta a la lista y al final no hace nada
	i = 0;
	aux = NULL;
	while (str[i])
	{
		pos = 0;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		flag = get_type(&str[i]);
		if (flag == 4 || flag == 5)
			token = token_new(ft_substr(str, i++, 1), flag);
		else if (flag == 6 || flag == 7)
		{
			token = token_new(ft_substr(str, i, 2), flag);
			i += 2;
		}
		else if (str[i] != ' ' && str[i])
		{
			if (flag == 2 || flag == 3 || flag == 8)
				i++;
			while (ft_isalnum(str[i + pos]) || \
			(flag != get_type(&str[i + pos]) && (flag == 2 || flag == 3)))
				pos++;
			token = token_new(ft_substr(str, i, pos), flag);
			if (flag == 2 || flag == 3)
				pos++;
		}
		i += pos;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		token->prev = aux;
		aux = token;
		//printf("str: %s\n", aux->str);
		token = token->next;
	}
	while (aux->prev)
	{
		//printf("token->str: %s\n", token->str);
		aux = aux->prev;
	}
	token = aux;
	while (token)
	{
		printf("token->str: %s\n", token->str);
		token = token->next;
	}
	//ft_print_tokens(token);
	return (aux);
}

int	init_vars(char *line, t_shell *shell)
{
	t_command	*aux;
	char		**split;
	int			i;

	i = -1;
	shell->command = command_new();
	split = ft_split_shell(line);
	// for(int j = 0; split[j]; j++)
	// 	printf("%s\n", split[j]);
	aux = shell->command;
	while (split[++i])
	{
		aux->token = put_tokens(aux->token, split[i]);
		if (!aux->token)
		{
			printf("Token es null\n");
			return (0);
		}
		aux = aux->next;
		aux = command_new();
	}
	//free(split);
	// while (shell->command)
	// {
	// 	while (shell->command->token)
	// 	{
	// 		printf("%s\n", shell->command->token->str);
	// 		shell->command->token = shell->command->token->next;
	// 	}
	// 	shell->command = shell->command->next;
	// }

	return (0);
}


// echo hola > out|pwd
// |
// ft_split_shell
// |
// echo hola > out
// pwd
// NULL