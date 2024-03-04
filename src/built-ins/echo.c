/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:19 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 17:57:45 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function searches for the '-n' flag in the given string. If the flag is
	present, it returns 1. This enables the echo built-in function to mimic the
	behavior of the echo command in bash when used with this flag.
*/

int	is_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

/*
	This function replicates the behavior of the echo command in bash. It
	utilizes the 'is_flag_n' function to determine if the '-n' flag is present,
	updating the flag accordingly. If the flag is present, it is skipped, and the
	function proceeds to print all the given arguments. After printing all
	arguments, it checks if the flag is '-n'; if not found, it prints a newline
	character.
*/

void	my_echo(t_shell *shell)
{
	int		i;
	int		flag;
	char	**cmd;

	i = 1;
	flag = 0;
	cmd = shell->command->cmd;
	while (cmd[i] && !is_flag_n(cmd[i]))
		flag = ++i;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if ((cmd[i + 1]))
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	shell->end_type = 0;
}
