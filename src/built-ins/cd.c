/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:36:28 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/28 11:06:24 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_cd(t_shell *shell)
{
	char	*dir;
	int		value;

	value = 0;
	dir = shell->command->cmd[1];
	value = chdir(dir);
	if (!access(dir, F_OK) && value == -1)
	{
		if (access(dir, X_OK) == -1)
			return (perm_den2(shell, dir));
	}
	else if (value == -1)
	{
		dup2(2, 1);
		printf("minishell: cd: %s: No such file or directory\n", dir);
		shell->end_type = 1;
		dup2(shell->command->out_copy, 1);
		return (clear_program(shell, 1, 0));
	}
	shell->end_type = 0;
	return (1);
}
