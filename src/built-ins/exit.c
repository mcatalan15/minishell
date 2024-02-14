/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 13:15:50 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_shell *shell)
{
	ft_putstr_fd("exit\n", shell->command->out_copy);
	dprintf(shell->command->out_copy, "mem: %p\n", shell->command->);
	free_prompt(shell);
	clear_program(shell, 0, 1);
}
