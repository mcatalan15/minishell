/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:13:50 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/08 20:16:43 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_cmd(t_token *token)
{
	int		i;
	char	**command;
	t_token	*aux;

	i = cmdlen(token);
	aux = token;
	command = malloc((i + 1) * sizeof(char *));
	if (!command)
		return (NULL);
	i = 0;
	while (aux && aux->type != T_PIPE)
	{
		if ((!aux->prev || (aux->prev && (aux->prev->type < T_REDIN
						|| aux->prev->type > T_DOUT))) && aux->type == T_STR)
			command[i++] = aux->str;
		aux = aux->next;
	}
	command[i] = NULL;
	//ft_print_cmd(command);
	return (command);
}

char	*get_path(t_shell *shell)
{
	int		i;
	char	**split;
	char	*path;

	path = NULL;
	i = -1;
	while (shell->env[++i])
	{
		if (!ft_strcmpc(shell->env[i], "PATH", '='))
		{
			split = ft_split(ft_strchr(shell->env[i], '=') + 1, ':');
			if (!split)
				return (NULL);
			path = search_path(shell, split);
			break ;
		}
	}
	return (path);
}

void	exec_cmd(t_shell *shell, t_token *aux)
{
	shell->command->cmd = get_cmd(aux);
	shell->command->path = get_path(shell);
	printf("path: %s\n", shell->command->path);
    exit(0);
}
