/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:29 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/08 20:04:29 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	t_redin(t_shell *shell, t_token *token)
// {
// 	shell->command->fdin = open(token->str, O_RDONLY);
// 	if (shell->command->fdin == -1)
// 		rdir_erro(shell, 1);
// 	dup2(shell->command->fdin, 0);
// }

// void	t_redout(t_shell *shell, t_token *token)
// {
// 	shell->command->fdout = open(token->str, O_WRONLY | O_CREAT | O_TRUNC);
// 	dup2(shell->command->fdout, 1);
// }

// void	t_dout(t_shell *shell, t_token *token)
// {
// 	shell->command->fdout = open(token->str, O_WRONLY | O_CREAT | O_APPEND);
// 	dup2(shell->command->fdout, 1);
// }

// void	here_doc(t_shell *shell, t_token *token)
// {
// 	char	*line;

// 	dup2(shell->command->in_copy, 0);
// 	pipe(shell->command->fd);
// 	dup2(shell->command->fd[0], 1);
// 	line = ft_strdup("\0");
// 	while (ft_strcmp(line, token->str))
// 	{
// 		free(line);
// 		line = get_next_line(0);
// 		printf("%s", line);
// 	}
// 	free(line);
// 	dup2(shell->command->fd[1], 0);
// }

// void	redirect(t_shell *shell, t_token *token)
// {
// 	int	type;

// 	if (token->prev)
// 		type = token->type;
// 	if (type == T_REDIN)
// }
