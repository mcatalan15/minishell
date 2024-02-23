/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:30 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/23 12:35:12 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**remove_from_env(t_shell *shell, int pos)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i));
	if (!new_env)
		malloc_err(shell);
	i = -1;
	while (shell->env[++i])
	{
		if (i < pos)
			new_env[i] = ft_strdup(shell->env[i]);
		else if (i > pos)
			new_env[i - 1] = ft_strdup(shell->env[i]);
	}
	new_env[i - 1] = NULL;
	free_dp(shell->env, NULL);
	return (new_env);
}

int	search_id_pos(char **env, char *id)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(id);
	while (env[++i])
	{
		if (ft_strncmp(id, env[i], len) == 0 && env[i][len] == '=')
			return (i);
	}
	return (-1);
}

void	my_unset(t_shell *shell)
{
	char	**id;
	int		i;
	int		pos;

	i = 0;
	id = shell->command->cmd;
	while (id[++i])
	{
		pos = search_id_pos(shell->env, id[i]);
		printf("%d\n", pos);
		if (pos != -1)
			shell->env = remove_from_env(shell, pos);
	}
}
