/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:04:55 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/01 12:29:42 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	stx_erro(t_shell *shell, char c)
{
	int		fd;
	char	*s;
	char	*s2;

	s = "minishell: syntax error near unexpected token `newline'\n";
	s2 = "minishell: syntax error due to quotes unclosed\n";
	fd = dup(1);
	dup2(2, 1);
	if (c == '\n')
		printf("%s", s);
	else if (c == '\"')
		printf("%s", s2);
	else
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	dup2(fd, 1);
	shell->end_type = 258;
	return (clear_list(shell, STX_ERRO, 0));
}

void	rdir_erro(int type)
{
	(void)type;
}

void	exec_erro(int type)
{
	(void)type;
}
