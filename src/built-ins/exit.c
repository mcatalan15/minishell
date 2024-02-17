/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/17 15:12:51 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_shell *shell)
{
	ft_putstr_fd("exit\n", shell->command->out_copy);
	free_prompt(shell);
	free_dp(shell->env, NULL);
	clear_program(shell, 0, 1);
}
// dprintf(shell->command->out_copy, "mem: %p\n", shell->command->);
