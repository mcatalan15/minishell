/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:13:50 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/27 13:21:23 by mcatalan         ###   ########.fr       */
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
	command[i] = NULL;
	i = 0;
	while (aux && aux->type != T_PIPE)
	{
		if ((!aux->prev || !ft_isrd(aux->prev->type)) && aux->type == T_STR)
			command[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
	return (command);
}

char	*get_path(t_shell *shell)
{
	int		i;
	char	**split;
	char	*path;

	path = NULL;
	i = -1;
	if (!*shell->command->cmd)
		return (NULL);
	if (ft_strchr(shell->command->cmd[0], '/'))
		return (get_path_when_cmd(shell));
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

void	redirect(t_shell *shell, t_token *list, int pid_num)
{
	t_token	*aux;

	aux = list;
	while (aux && aux->type != T_PIPE)
	{
		if (aux->next && ft_isrd(aux->type) && \
		(aux->next->type == T_STR || aux->next->type == T_DOLLAR))
			redirection(shell, aux, pid_num);
		aux = aux->next;
	}
}

void	execute(t_shell *shell)
{
	int	builtin;

	builtin = ft_isbuiltin(shell->command->cmd[0]);
	if (builtin)
		manage_builtins(shell, builtin);
	else
		execve(shell->command->path, shell->command->cmd, shell->env);
}

int	exec_cmd(t_shell *shell, t_token *aux, int pid, int pid_num)
{
	redirect(shell, aux, pid_num);
	if (!ft_isbuiltin(shell->command->cmd[0]))
		shell->command->path = get_path(shell);
	execute(shell);
	if (!pid)
		exit(0);
	if (!shell->command)
		return (0);
	return (1);
}

// dprintf(shell->command->out_copy,"path: %s", shell->command->path);
