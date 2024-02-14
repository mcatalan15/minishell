/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:04:55 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 12:29:31 by mcatalan         ###   ########.fr       */
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
	else if (c == 'a')
		printf("minishell: syntax error to many arguments\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	dup2(fd, 1);
	shell->end_type = STX_ERRO;
	return (clear_program(shell, STX_ERRO, 0));
}

void	nsf_or_dir(t_shell *shell, int type, char *str)
{
	char	*s;

	s = "No such file or directory";
	dup2(2, 1);
	printf("minishell: %s: %s\n", str, s);
	dup2(shell->command->out_copy, 1);
	shell->end_type = 1;
	clear_program(shell, type, 1);
}

void	perm_den(t_shell *shell, char *cmd)
{
	dup2(2, 1);
	printf("minishell: %s: Permission denied\n", cmd);
	dup2(shell->command->out_copy, 1);
	clear_program(shell, NO_PERM, 1);
}

void	cmd_nf(t_shell *shell, char *cmd)
{
	dup2(2, 1);
	printf("minishell: %s: Command not found\n", cmd);
	dup2(shell->command->out_copy, 1);
	clear_program(shell, PATH_ERROR, 1);
}

void	rdir_erro(t_shell *shell, int type, char *str)
{
	char	*s;

	s = "Redirection error";
	dup2(2, 1);
	printf("minishell: %s: %s\n", str, s);
	dup2(shell->command->out_copy, 1);
	shell->end_type = 1;
	clear_program(shell, type, 1);
}
