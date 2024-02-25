/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/25 21:13:05 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_shell *shell)
{
	printf("exit\n");
	free_prompt(shell);
	free_dp(shell->env, NULL);
	if (shell->command->token->next)
		clear_program(shell, 255, 1);
	clear_program(shell, 0, 1);
}
// dprintf(shell->command->out_copy, "mem: %p\n", shell->command->);
