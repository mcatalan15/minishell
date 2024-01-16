/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/16 22:26:09 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  get_type(char *str)
{
    if (ft_isalnum(str[0]))
        return (1);
    if (str[0] == '\"')
        return (3);
    if (str[0] == '\'')
        return (4);
    if (str[0] == ' ')
        return (2);
    if (str[0] == '>' && str[1] != '>')
        return (5);
    if (str[0] == '<' && str[1] != '<')
        return (6);
    if (str[0] == '>' && str[1] == '>')
        return (7);
    if (str[0] == '<' && str[1] == '<')
        return (8);
    if (str[0] == '$' && str[1])
        return (10);
    return (0);
}

static t_token *token_new(char *str, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->str = str;
    token->type = type;
    token->next = NULL;
    token->prev = NULL;
    return (token);
}

static t_command *command_new(void)
{
    t_command *command_new;

    command_new = malloc(sizeof(t_command));
    if (!command_new)
        return (NULL);
    command_new->cmd = NULL;
    command_new->path = NULL;
    command_new->next = NULL;
    command_new->prev = NULL;
    return (command_new);
}

static t_token  *put_tokens(t_token *token, char *str)
{
    int       i;
    int       pos;
    int       flag;
    t_token   *aux;
    
    // la lista se crea pero aux no apunta a la lista y al final no hace nada
    i = -1;
    aux = token;
    while (str[++i])
    {
        pos = 0;
        flag = get_type(&str[i]);
        if (flag == 5 || flag == 6)
            token = token_new(ft_substr(str, i++, 1), flag);
        else if (flag == 7 || flag == 8)
        {
            token = token_new(ft_substr(str, i, 2), flag);
            i += 2;
        }
        else
        {
            pos++;
            while (ft_isalnum(str[i + pos]) || \
            (flag != get_type(&str[i + pos]) && flag == 3 && flag == 4))
                pos++;
            token = token_new(ft_substr(str, i, pos), flag);
        }
        i += pos;
        token = token->next;
    }
    token = aux;
    while (aux)
    {
        printf("%s\n", aux->str);
        aux = aux->next;
    }
    return (aux);
}


int init_vars(char *line, t_shell *shell)
{
	char **split;
	t_command   *aux;
	int         i;

	i = -1;
	shell->command = command_new();
	split = ft_split_shell(line);
	aux = shell->command;
	while (split[++i])
	{
	    aux->token = put_tokens(aux->token, split[i]);
	    if (!aux->token)
	    aux = aux->next;
	    aux = command_new();
	}

	while (shell->command)
	{
	    while (shell->command->token)
	    {
	        printf("%s\n", shell->command->token->str);
	        shell->command->token = shell->command->token->next;
	    }
	    shell->command = shell->command->next;
	}

	return (0);
}

// int init_vars(char *line, t_shell *shell)
// {
//     char        **split;

//     split = ft_split_shell(line);
// 	for(int i = 0; split[i]; i++)
// 		printf("%s\n", split[i]);
// 	(void)shell;    
//     return (0);
// }

// echo hola > out|pwd
// |
// ft_split_shell
// |
// echo hola > out
// pwd
// NULL