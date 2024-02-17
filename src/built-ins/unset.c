/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:30 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/17 15:01:23 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**remove_from_env(t_shell *shell, int pos)
{
	char	**new_env;
	char	**env;
	int		i;

	i = 0;
	env = envdup(shell->env);
	free_dp(shell->env, NULL);
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i -1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (i < pos)
			new_env[i] = ft_strdup(env[i]);
		else if (i > pos)
			new_env[i - 1] = ft_strdup(env[i]);
	}
	new_env[i - 1] = NULL;
	free_dp(env, NULL);
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
		if (pos != -1)
			shell->env = remove_from_env(shell, pos);
	}
}
