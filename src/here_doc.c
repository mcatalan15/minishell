/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:05:48 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/29 19:04:33 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_shell *shell, t_token *token, int pos)
{
	char	*line;
	char	*del;
	int		fd[2];

	wait_signal(HERE_DOC); //-> execution signals
	dup2(shell->command->in_copy, 0);
	pipe(fd);
	del = ft_strjoin(token->str, "\n");
	ft_putstr_fd("> ", shell->command->out_copy);
	line = get_next_line(0);
	while (line && ft_strcmp(line, del) != 0)
	{
		ft_putstr_fd(line, fd[1]);
		free(line);
		ft_putstr_fd("> ", shell->command->out_copy);
		line = get_next_line(0);
	}
	if (!line)
	{
		close(fd[1]);
		close(fd[0]);
	}
	free(line);
	free(del);
	shell->command->hd[pos] = dup(fd[0]);
	close(fd[1]);
	close(fd[0]);
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
		return (0);
	while (list->next)
	{
		if (list->type == T_DIN)
			here_doc(shell, list->next, i);
		if (list->type == T_PIPE)
			i++;
		list = list->next;
	}
	return (1);
}
