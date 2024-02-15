/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:25 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/15 13:05:45 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	id_checker(char *s)
// {
// 	if (s[0] )
// }

int	ft_is_equal(char *cmd, int flag)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			flag = i;
	}
	return (flag);
}

// char	*add_to_env(char *cmd)
// {
// 	int		i;
// }

void	my_export(t_shell *shell)
{
	char	**cmd;
	char	*id;
	char	*value;
	int		i;
	int		flag;

	id = NULL;
	value = NULL;
	flag = 0;
	cmd = shell->command->cmd;
	if (cmd[2] != NULL)
		stx_erro(shell, 'a');
	flag = ft_is_equal(cmd[1], flag);
	id = malloc(sizeof(char) * (flag + 1));
	value = malloc(sizeof(char) * (ft_strlen(cmd[1]) - flag + 1));
	
	i = -1;
	while (flag > ++i)
		id[i] = cmd[1][i];
	i = -1;
	// id_checker(id);
	printf("cmd: %sid: %s\n", shell->command->cmd[1], id);
	free(id);
	free(value);
}

//bash: export: `1A=ads': not a valid identifier
//bash: export: `=': not a valid identifier