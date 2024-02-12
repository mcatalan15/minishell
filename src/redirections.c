/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:29 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/12 19:24:10 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	t_redin(t_shell *shell, t_token *token)
{
	shell->command->fdin = open(token->str, O_RDONLY);
	if (shell->command->fdin == -1)
		rdir_erro(shell, 1);
	dup2(shell->command->fdin, 0);
}

void	t_redout(t_shell *shell, t_token *token)
{
	shell->command->fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(shell->command->fdout, 1);
}

void	t_dout(t_shell *shell, t_token *token)
{
	shell->command->fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	dup2(shell->command->fdout, 1);
}

// https://github.com/JuliaORS/Minishell-42Bcn/blob/main/srcs/execution/heredoc.c

void	here_doc(t_shell *shell, t_token *token)
{
	char	*line;
	int		fd[2];
	char	*del;

	dup2(shell->command->in_copy, 0);
	pipe(fd);
	del = ft_strjoin(token->str, "\n");
	ft_putstr_fd("> ", shell->command->out_copy);
	line = get_next_line(0);
	while (ft_strcmp(line, del) != 0)
	{
		free(line);
		ft_putstr_fd(line, fd[1]);
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
