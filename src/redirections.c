/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:29 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/15 10:43:59 by mcatalan         ###   ########.fr       */
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

void	here_doc(t_shell *shell, t_token *token)
{
	char	*line;
	int		fd[2];
	char	*del;

	//dprintf(shell->command->in_copy, "iep\n");
	dup2(shell->command->in_copy, 0);
	pipe(fd);
	del = ft_strjoin(token->str, "\n");
	ft_putstr_fd("> ", shell->command->out_copy);
	line = get_next_line(0);
	while (ft_strcmp(line, del) != 0)
	{
		ft_putstr_fd(line, fd[1]);
		free(line);
		ft_putstr_fd("> ", shell->command->out_copy);
		line = get_next_line(0);
	}
	free(line);
	free(del);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

void	redirection(t_shell *shell, t_token *token)
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
		here_doc(shell, token->next);
}
