/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:13:50 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/12 19:25:42 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_cmd(t_token *token)
{
	int		i;
	char	**command;
	t_token	*aux;

	i = cmdlen(token);
	//printf("malloced: %d\n", i);
	aux = token;
	command = malloc((i + 1) * sizeof(char *));
	if (!command)
		return (NULL);
	command[i] = NULL;
	i = 0;
	while (aux && aux->type != T_PIPE)
	{
		if ((!aux->prev || !ft_isrd(aux->prev->type)) && aux->type == T_STR)
			command[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
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

void	redirect(t_shell *shell, t_token *list)
{
	t_token	*aux;

	aux = list;
	while (aux && aux->type != T_PIPE)
	{
		if (aux->next && ft_isrd(aux->type) && aux->next->type == T_STR)
			redirection(shell, aux);
		aux = aux->next;
	}
}

void	exec_cmd(t_shell *shell, t_token *aux)
{
	// int	i;

	// i = -1;
	shell->command->cmd = get_cmd(aux);
	shell->command->path = get_path(shell);
	redirect(shell, aux);
	printf("llega\n");
	execve(shell->command->path, shell->command->cmd, shell->env);
	// if (!shell->command->cmd)
	// 	dprintf(shell->command->out_copy, "cmd = NULL \n");
	// while (shell->command->cmd[++i])
 	// 	dprintf(shell->command->out_copy, "cmd[%d]: %s\n", i, shell->command->cmd[i]);
	exit(1);
	// dprintf(shell->command->out_copy,"path: %s", shell->command->path);
}
