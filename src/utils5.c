/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:01:38 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 10:38:52 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

int	ft_isbuiltin(char *cmd)
{
	if (!ft_strcmpnks(cmd, "echo"))
		return (1);
	if (!ft_strcmpnks(cmd, "export"))
		return (2);
	if (!ft_strcmpnks(cmd, "unset"))
		return (3);
	if (!ft_strcmpnks(cmd, "env"))
		return (4);
	if (!ft_strcmpnks(cmd, "cd"))
		return (5);
	if (!ft_strcmpnks(cmd, "pwd"))
		return (6);
	if (!ft_strcmpnks(cmd, "exit"))
		return (7);
	return (0);
}

int	*get_pid(t_token *token)
{
	int	len;
	int	*pid;

	len = 1;
	while (token)
	{
		if (token->type == T_PIPE)
			len++;
		token = token->next;
	}
	pid = malloc((len + 1) * sizeof(int));
	if (!pid)
		return (NULL);
	pid[len] = -1;
	return (pid);
}

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

