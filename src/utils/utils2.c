/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:01:38 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 20:25:04 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function checks if the command is a built-in command. If it is, it
	returns the corresponding number. If it is not, it returns 0.
*/

int	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (2);
	if (!ft_strcmp(cmd, "unset"))
		return (3);
	if (!ft_strcmp(cmd, "env"))
		return (4);
	if (!ft_strcmp(cmd, "cd"))
		return (5);
	if (!ft_strcmp(cmd, "pwd"))
		return (6);
	if (!ft_strcmp(cmd, "exit"))
		return (7);
	return (0);
}

/*
	This function waits for all the children to finish and returns the status
	of the last child.
*/

void	wait_for_children(t_shell *shell, int *pid)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	dup2(shell->command->in_copy, 0);
	dup2(shell->command->out_copy, 1);
	while (pid[++i] != -1)
		waitpid(pid[i], &status, 0);
	if (WIFEXITED(status) && (i != 1 || !ft_isbuiltin(shell->command->cmd[0])))
		shell->end_type = WEXITSTATUS(status);
}

int	ft_is_equal(char *cmd, int flag)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			flag = i;
	}
	if (!cmd[i])
		flag = i;
	return (flag);
}

char	*get_path_when_cmd(t_shell *shell)
{
	char	*path;

	if (!access(shell->command->cmd[0], F_OK))
	{
		if (access(shell->command->cmd[0], X_OK) == -1)
			perm_den(shell, shell->command->cmd[0]);
		path = ft_strdup(shell->command->cmd[0]);
		if (!path)
			malloc_err(shell);
		return (path);
	}
	nsf_or_dir(shell, PATH_ERROR, shell->command->cmd[0]);
	return (NULL);
}

int	ft_isalpha_lw(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (0);
	return (1);
}
