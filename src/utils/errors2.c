/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:51:21 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/27 19:20:34 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	nv_id(t_shell *shell, char *cmd, int type)
{
	dup2(2, 1);
	printf("minishell: export: `%s': not a valid identifier\n", cmd);
	dup2(shell->command->out_copy, 1);
	(void)type;
	shell->end_type = 1;
	return (1);
}

int	malloc_err(t_shell *shell)
{
	dup2(2, 1);
	printf("minishell: malloc: error in malloc\n");
	dup2(shell->command->out_copy, 1);
	shell->end_type = 1;
	return (clear_program(shell, EXIT_FAILURE, 0));
}

int	num_argre(char *cmd)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("minishell: exit: %s: numeric argument required\n", cmd);
	dup2(fd, 1);
	return (255);
}
