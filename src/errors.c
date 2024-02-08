/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:04:55 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/08 19:47:54 by mcatalan@st      ###   ########.fr       */
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
	return (clear_program(shell, STX_ERRO, 0));
}

void	rdir_erro(t_shell *shell, int type)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("minishell: %s: No such file or directory\n", shell->command->cmd[0]);
	dup2(fd, 1);
	shell->end_type = 1;
	clear_program(shell, type, 1);
}

void	perm_den(t_shell *shell, char *cmd)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("minishell: %s: Permission denied\n", cmd);
	dup2(fd, 1);
	clear_program(shell, NO_PERM, 1);
}

void	cmd_nf(t_shell *shell, char *cmd)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("minishell: %s: Command not found\n", cmd);
	dup2(fd, 1);
	clear_program(shell, PATH_ERROR, 1);
}

void	exec_erro(int type)
{
	(void)type;
}
