/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/29 12:49:48 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_errors(char **cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ft_isspace(cmd[1][i]))
		i++;
	if ((cmd[1][i] == '+' || cmd[1][i] == '-'))
			i++;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]) && (!ft_isspace(cmd[1][i]) || !flag))
			return (num_argre(cmd[1]));
		if (flag || cmd[1][i] != '0' || \
		ft_isspace(cmd[1][i + 1]) || !cmd[1][i + 1])
			flag++;
		i++;
	}
	if (i == 0 || !flag || flag > 10)
		return (num_argre(cmd[1]));
	if (cmd[2])
		return (too_manyargs());
	return (ft_atoi(cmd[1]));
}

void	my_exit(t_shell *shell)
{
	unsigned int	type;

	type = (unsigned int)shell->end_type;
	g_signal = type;
	printf("exit\n");
	free_prompt(shell);
	free_dp(shell->env, NULL);
	if (shell->command)
	{
		if (shell->command->token->next)
			type = exit_errors(shell->command->cmd);
	}
	clear_program(shell, type, 1);
	exit(type);
}
// dprintf(shell->command->out_copy, "mem: %p\n", shell->command->);
