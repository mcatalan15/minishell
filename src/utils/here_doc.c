/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:05:48 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/20 12:11:05 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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


