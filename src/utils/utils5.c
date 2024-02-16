/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:01:38 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/16 13:20:45 by mcatalan         ###   ########.fr       */
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
	if (WIFEXITED(status))
		shell->end_type = WEXITSTATUS(status);
}