/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:14 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/03 18:35:02 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function behaves as the env command in bash.
	If no arguments are given, it prints the environment variables.
*/

void	my_env(t_shell *shell)
{
	int	i;

	if (!shell->command->cmd[1])
	{
		i = -1;
		while (shell->env[++i])
			printf("%s\n", shell->env[i]);
	}
	else
		nsf_or_dir2(shell, shell->command->cmd[1]);
	shell->end_type = 0;
}
