/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:29 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 10:37:48 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	t_redin(t_shell *shell, t_token *token)
{
	int	fdin;

	if (access(token->str, F_OK) == -1)
		nsf_or_dir(shell, 1, token->str);
	if (access(token->str, R_OK) == -1)
		perm_den(shell, token->str);
	fdin = open(token->str, O_RDONLY);
	if (fdin == -1)
		rdir_erro(shell, 1, token->str);
	dup2(fdin, 0);
}

void	t_redout(t_shell *shell, t_token *token)
{
	int	fdout;

	if (!access(token->str, F_OK))
	{
		if (access(token->str, W_OK) == -1)
			perm_den(shell, token->str);
	}
	fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdout == -1)
		rdir_erro(shell, 1, token->str);
	dup2(fdout, 1);
}

void	t_din(t_shell *shell, int pid_num)
{
	dup2(shell->command->hd[pid_num], 0);
}

void	t_dout(t_shell *shell, t_token *token)
{
	int	fdout;

	if (!access(token->str, F_OK))
	{
		if (access(token->str, W_OK) == -1)
			perm_den(shell, token->str);
	}
	fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fdout == -1)
		rdir_erro(shell, 1, token->str);
	dup2(fdout, 1);
}

void	redirection(t_shell *shell, t_token *token, int pid_num)
{
	int	type;

	type = token->type;
	if (type == T_REDIN)
		t_redin(shell, token->next);
	else if (type == T_REDOUT)
		t_redout(shell, token->next);
	else if (type == T_DOUT)
		t_dout(shell, token->next);
	else if (type == T_DIN)
		t_din(shell, pid_num);
}
