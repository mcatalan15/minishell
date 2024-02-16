/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:19 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/16 13:22:17 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_echo(t_shell *shell)
{
	int		i;
	int		flag;
	char	**cmd;

	i = 0;
	flag = 0;
	cmd = shell->command->cmd;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		flag = 1;
	if (flag)
		i++;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if ((cmd[i + 1] && *(cmd[i])))
			printf(" ");
	}
	if (!flag)
		printf("\n");
	
}
