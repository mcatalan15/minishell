/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:04:55 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 13:59:25 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	stx_erro(t_shell *shell, char c)
{
	//int		fd;
	// char	*s;
	// char	*s2;
	(void)c;

	// s = "minishell: syntax error near unexpected token `newline'\n";
	// s2 = "minishell: syntax error due to quotes unclosed\n";
	// fd = dup(1);
	// dup2(STDERR_FILENO, STDOUT_FILENO);
	// if (c == '\n')
	// 	printf("%s", s);
	// else if (c == '\"')
	// 	printf("%s", s2);
	// else if (c == 'a')
	// 	printf("minishell: syntax error too many arguments\n");
	// else
	// 	printf("minishell: syntax error near unexpected token `%c'\n", c);
	// dup2(fd, 1);
	ft_putstr_fd("syntax error\n", 2);
	shell->end_type = STX_ERRO;
	return (clear_program(shell, STX_ERRO, 0));
}

void	nsf_or_dir(t_shell *shell, int type, char *str)
{
	(void)type;
	(void)str;
	// char	*s;

	// s = "No such file or directory";
	// dup2(2, 1);
	// printf("minishell: %s: %s\n", str, s);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("No such file or directory\n", 2);
	shell->end_type = type;
	clear_program(shell, type, 1);
}

void	nsf_or_dir2(t_shell *shell, char *str)
{
	(void)str;
	// char	*s;

	// s = "No such file or directory";
	// dup2(STDERR_FILENO, 1);
	// printf("%s: %s: %s\n", shell->command->cmd[0], str, s);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("No such file or directory\n", 2);
	shell->end_type = PATH_ERROR;
	clear_program(shell, PATH_ERROR, 0);
}

int	perm_den2(t_shell *shell, char *dir)
{
	(void)dir;
	// dup2(2, 1);
	// printf("minishell: cd: %s: Permission denied\n", dir);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("Permission denied\n", 2);
	shell->end_type = 1;
	clear_program(shell, 1, 0);
	return (0);
}

void	perm_den(t_shell *shell, char *cmd)
{
	(void)cmd;
	// dup2(2, 1);
	// printf("minishell: %s: Permission denied\n", cmd);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("Permission denied\n", 2);
	clear_program(shell, NO_PERM, 1);
}
