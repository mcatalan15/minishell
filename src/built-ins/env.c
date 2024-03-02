/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:14 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 12:06:33 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function behaves as the env command in bash.
	Search if the
*/
//acabar/cambiar header
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
		nsf_or_dir2(shell, shell->command->cmd[1]); //->cambiar a not arguments or flags need
	shell->end_type = 0;
}
