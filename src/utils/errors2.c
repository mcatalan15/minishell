/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:51:21 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/02 14:01:34 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_nf(t_shell *shell, char *cmd)
{
	(void)cmd;
	// dup2(2, 1);
	// printf("minishell: %s: command not found\n", cmd);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("command not found\n", 2);
	clear_program(shell, PATH_ERROR, 1);
}

void	rdir_erro(t_shell *shell, int type, char *str)
{
	// char	*s;

	(void)str;
	// s = "Redirection error";
	// dup2(2, 1);
	// printf("minishell: %s: %s\n", str, s);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("Redirection error\n", 2);
	shell->end_type = 1;
	clear_program(shell, type, 1);
}

int	nv_id(t_shell *shell, char *cmd, int type)
{
	(void)cmd;
	// dup2(2, 1);
	// printf("minishell: export: `%s': not a valid identifier\n", cmd);
	// dup2(shell->command->out_copy, 1);
	ft_putstr_fd("not a valid identifier\n", 2);
	(void)type;
	shell->end_type = 1;
	return (1);
}

int	malloc_err(t_shell *shell)
{
	ft_putstr_fd("error in malloc\n", 2);
	// dup2(2, 1);
	// printf("minishell: malloc: error in malloc\n");
	// dup2(shell->command->out_copy, 1);
	shell->end_type = 1;
	return (clear_program(shell, EXIT_FAILURE, 0));
}

int	num_argre(char *cmd)
{
	// int	fd;

	(void)cmd;
	// fd = dup(1);
	// dup2(2, 1);
	// printf("minishell: exit: %s: numeric argument required\n", cmd);
	// dup2(fd, 1);
	ft_putstr_fd("numeric argument required\n", 2);
	return (255);
}
