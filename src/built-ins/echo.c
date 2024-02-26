/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:19 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/26 12:36:40 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	my_echo(t_shell *shell)
{
	int		i;
	int		flag;
	char	**cmd;

	i = 0;
	flag = 0;
	cmd = shell->command->cmd;
	if (cmd[1] && !is_flag_n(cmd[1]))
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
