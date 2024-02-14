/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:14 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 12:28:42 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_env(t_shell *shell)
{
	int	i;

	if (ft_strcmp(shell->command->cmd[0], "env"))
	{
		i = -1;
		while (shell->env[++i])
			printf("%s\n", shell->env[i]);
		exit(0);
	}
	else
		stx_erro(shell, 'a');
}
