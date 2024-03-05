/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:22 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/05 18:57:05 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function handles errors related to the exit command. If the exit
	command is executed with more than one argument or with non-numerical
	characters, it prints an error message and returns 1. If the exit command
	is successful, it returns the number of the argument given.
*/

int	exit_errors(t_shell *shell)
{
	int		i;
	int		flag;
	char	**cmd;

	i = 0;
	flag = 0;
	cmd = shell->command->cmd;
	while (ft_isspace(cmd[1][i]))
		i++;
	if ((cmd[1][i] == '+' || cmd[1][i] == '-'))
		i++;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]) && (!ft_isspace(cmd[1][i]) || !flag))
			return (num_argre(shell));
		if (flag || cmd[1][i] != '0' || \
		ft_isspace(cmd[1][i + 1]) || !cmd[1][i + 1])
			flag++;
		i++;
	}
	if (i == 0 || !flag || flag > 10)
		return (num_argre(shell));
	if (cmd[2])
		return (too_manyargs(shell));
	return (clear_program(shell, ft_atoi(cmd[1]), 1));
}

/*
	This function behave as the exit function and is also used in case of
	ctrl-D, to exit the minishell. Prints an 'exit' output and clears all
	the program.
*/

void	my_exit(t_shell *shell)
{
	unsigned int	type;

	type = (unsigned int)shell->end_type;
	g_signal = type;
	if (is_father(shell))
		printf("exit\n");
	free_prompt(shell);
	if (shell->command)
	{
		if (shell->command->token->next)
			type = exit_errors(shell);
		else
		{
			free_dp(shell->env, NULL);
			clear_program(shell, type, 1);
		}
		shell->end_type = type;
	}
	else
	{
		free_dp(shell->env, NULL);
		exit (type);
	}
}
