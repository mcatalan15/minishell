/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/23 12:50:27 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_shell *shell)
{
	printf("exit\n");
	free_prompt(shell);
	free_dp(shell->env, NULL);
	clear_program(shell, 0, 1);
}
// dprintf(shell->command->out_copy, "mem: %p\n", shell->command->);
