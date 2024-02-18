/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:51:21 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/18 13:52:14 by mcatalan@st      ###   ########.fr       */
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
