/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:29 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/03 21:06:52 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function redirects the standard input to the file given as argument.
	Also, it checks if the file exists and if it has the right permissions.
*/

int	t_redin(t_shell *shell, t_token *token)
{
	int	fdin;

	if (access(token->str, F_OK) == -1)
	{
		dup2(shell->command->in_copy, 0);
		nsf_or_dir(shell, 1, token->str);
		return (0);
	}
	if (access(token->str, R_OK) == -1)
	{
		dup2(shell->command->in_copy, 0);
		perm_den2(shell, shell->command->cmd[0]);
		return (0);
	}
	fdin = open(token->str, O_RDONLY);
	if (fdin == -1)
	{
		dup2(shell->command->in_copy, 0);
		rdir_erro(shell, 1, shell->command->cmd[0]);
		return (0);
	}
	dup2(fdin, 0);
	return (1);
}

/*
	This function redirects the standard output to the file given as argument.
	Also, it checks if the file exists and if it has the right permissions.
*/

int	t_redout(t_shell *shell, t_token *token)
{
	int	fdout;

	if (!access(token->str, F_OK))
	{
		if (access(token->str, W_OK) == -1)
		{
			dup2(shell->command->out_copy, 1);
			perm_den2(shell, shell->command->cmd[0]);
			return (0);
		}
	}
	fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdout == -1)
	{
		dup2(shell->command->out_copy, 1);
		nsf_or_dir(shell, 1, token->str);
		return (0);
	}
	dup2(fdout, 1);
	return (1);
}

/*
	This function redirects the standard input to the file descriptor given as
	argument. It is used for the heredoc.
*/

void	t_din(t_shell *shell, int pid_num)
{
	dup2(shell->command->hd[pid_num], 0);
}

/*
	This function redirects the standard output to the file given as argument.
	Also, it checks if the file exists and if it has the right permissions.
*/

int	t_dout(t_shell *shell, t_token *token)
{
	int	fdout;

	if (!access(token->str, F_OK))
	{
		if (access(token->str, W_OK) == -1)
		{
			dup2(shell->command->out_copy, 1);
			perm_den2(shell, shell->command->cmd[0]);
			return (0);
		}
	}
	fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fdout == -1)
	{
		dup2(shell->command->out_copy, 1);
		rdir_erro(shell, 1, shell->command->cmd[0]);
		return (0);
	}
	dup2(fdout, 1);
	return (1);
}

/*
	This function redirects the standard input and output to the file given as
	argument.
*/

int	redirection(t_shell *shell, t_token *token, int pid_num)
{
	int	type;

	type = token->type;
	if (type == T_REDIN)
		type = t_redin(shell, token->next);
	else if (type == T_REDOUT)
		type = t_redout(shell, token->next);
	else if (type == T_DOUT)
		type = t_dout(shell, token->next);
	else if (type == T_DIN)
		t_din(shell, pid_num);
	return (type);
}
