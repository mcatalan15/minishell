/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:05:48 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/03 18:48:01 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc(t_shell *shell, t_token *token, int pos)
{
	char	*line;
	int		status;
	int		pid;
	int		fd[2];

	dup2(shell->command->in_copy, 0);
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		wait_signal(HERE_DOC);
		line = readline("> ");
		while (line && (ft_strcmp(line, token->str) != 0))
		{
			ft_putstr_fd(line, fd[1]);
			free(line);
			line = readline("> ");
			write(fd[1], "\n", 1);
		}
		free(line);
		close(fd[1]);
		close(fd[0]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	shell->end_type = WEXITSTATUS(status);
	if (shell->end_type == 1)
		return (0);
	shell->command->hd[pos] = dup(fd[0]);
	close(fd[1]);
	close(fd[0]);
	return (1);
}

int	manage_hd(t_shell *shell, t_token *list)
{
	int		len;
	int		i;
	t_token	*aux;

	len = 1;
	i = 0;
	aux = list;
	while (aux->next)
	{
		if (aux->type == T_PIPE)
			len++;
		aux = aux->next;
	}
	shell->command->hd = ft_calloc((len + 1), sizeof(int));
	if (!shell->command->hd)
		malloc_err(shell);
	while (list->next)
	{
		if (list->type == T_DIN)
			if (!here_doc(shell, list->next, i))
				return (0);
		if (list->type == T_PIPE)
			i++;
		list = list->next;
	}
	return (1);
}
