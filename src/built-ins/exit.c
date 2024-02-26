/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/26 13:15:32 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_errors(char **cmd)
{
	int	i;

	i = -1;
	if (cmd[1][0] == '+' || cmd[1][0] == '-')
		i++;
	while (cmd[1][++i])
	{
		if (!ft_isdigit(cmd[1][i]))
			return (num_argre(cmd[1]));
	}
	if (cmd[2])
		return (too_manyargs());
	return (ft_atoi(cmd[1]));
}

void	my_exit(t_shell *shell)
{
	unsigned int	type;

	type = 0;
	printf("exit\n");
	free_prompt(shell);
	free_dp(shell->env, NULL);
	if (shell->command->token->next)
		type = exit_errors(shell->command->cmd);
	clear_program(shell, type, 1);
}
// dprintf(shell->command->out_copy, "mem: %p\n", shell->command->);
