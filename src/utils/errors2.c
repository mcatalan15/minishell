/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:51:21 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/22 11:42:25 by mcatalan         ###   ########.fr       */
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
	// clear_program(shell, type, 0);
	(void)type;
	return (0);
	// CHANGE -> bash: export: `1a=hola': not a valid identifier
}

int	malloc_err(t_shell *shell)
{
	dup2(2, 1);
	printf("minishell: malloc: error in malloc\n");
	dup2(shell->command->out_copy, 1);
	shell->end_type = 1;
	return (clear_program(shell, EXIT_FAILURE, 0));
}