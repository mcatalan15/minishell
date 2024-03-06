/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:13:50 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/06 09:29:35 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function returns the command malloced and filled with the strings of
	the tokens. Giving to execve the command to execute.
*/

char	**get_cmd(t_token *token)
{
	int		i;
	char	**command;
	t_token	*aux;

	i = cmdlen(token);
	aux = token;
	command = malloc((i + 1) * sizeof(char *));
	if (!command)
		malloc_err(token->shell);
	i = 0;
	while (aux && aux->type != T_PIPE)
	{
		if ((!aux->prev || !ft_isrd(aux->prev->type)) && \
		aux->type == T_STR && aux->str)
		{
			command[i] = ft_strdup(aux->str);
			if (!command[i++])
				malloc_err(token->shell);
		}
		aux = aux->next;
	}
	command[i] = NULL;
	return (command);
}

/*
	This function returns the path of the command to execute. If the command
	is not found, it returns NULL.
*/

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
				malloc_err(shell);
			path = search_path(shell, split);
			break ;
		}
	}
	if (!shell->env[i])
		nsf_or_dir(shell, PATH_ERROR, shell->command->cmd[0]);
	return (path);
}

/*
	This function redirects the input and output of the command to the
	corresponding file.
*/

int	redirect(t_shell *shell, t_token *list, int pid_num)
{
	t_token	*aux;

	aux = list;
	while (aux && aux->type != T_PIPE)
	{
		if (aux->next && ft_isrd(aux->type) && \
		(aux->next->type == T_STR || aux->next->type == T_DOLLAR))
		{
			if (!redirection(shell, aux, pid_num))
				return (0);
		}
		aux = aux->next;
	}
	if (aux && aux->type == T_PIPE)
	{
		close(shell->command->fd[0]);
		close(shell->command->fd[1]);
	}
	return (1);
}

/*
	This function executes the command. If the command is a builtin, it calls
	the function to manage the builtin. If the command is not a builtin, it
	calls the function to execute the command.
*/

void	execute(t_shell *shell)
{
	int	builtin;

	builtin = ft_isbuiltin(shell->command->cmd[0]);
	if (builtin)
		manage_builtins(shell, builtin);
	else
		execve(shell->command->path, shell->command->cmd, shell->env);
}

/*
	TBC
*/

int	exec_cmd(t_shell *shell, t_token *aux, int pid, int pid_num)
{
	if (!redirect(shell, aux, pid_num))
		return (0);
	if (!ft_isbuiltin(shell->command->cmd[0]))
		shell->command->path = get_path(shell);
	execute(shell);
	if (!pid)
		exit(0);
	if (!shell->command)
		return (0);
	return (1);
}
