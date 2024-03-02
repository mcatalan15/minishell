/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:01:59 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/02 11:16:06 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	id_checker(char *s, t_shell *shell, int j)
{
	int	i;

	i = 0;
	if (!ft_isalpha_lw(s[0]))
	{
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	}
	if ((s[i] == '=' && i != 0))
		return (0);
	nv_id(shell, shell->command->cmd[j], 1);
	return (1);
}

char	**envdup(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL); // -> malloc_err(shell);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

void	iter_env(char **env, char **new, char *id, char *cmd)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	j = 0;
	flag = 0;
	while (env[++i])
	{
		if (ft_strcmpc(id, env[i], '=') <= 0 && !flag)
		{
			new[j++] = ft_strdup(cmd);
			flag = 1;
			if (ft_strcmpc(id, env[i], '=') < 0)
				i--;
		}
		else
			new[j++] = ft_strdup(env[i]);
	}
	if (!flag)
		new[j++] = ft_strdup(cmd);
	new[j] = NULL;
}

char	**add_to_env(t_shell *shell, char *cmd, char *id)
{
	char	**new;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new = malloc((i + 2) * sizeof(char *));
	if (!new)
		malloc_err(shell);
	iter_env(shell->env, new, id, cmd);
	free_dp(shell->env, NULL);
	return (new);
}

int	my_export(t_shell *shell)
{
	char	*cmd;
	char	*id;
	int		i;
	int		pos;
	int		j;

	id = NULL;
	pos = 0;
	j = 0;
	while (shell->command->cmd[++j])
	{
		//shell, pos, j
		cmd = shell->command->cmd[j];
		pos = ft_is_equal(cmd, pos);
		if (ft_strchr(cmd, '='))
		{
			id = malloc(sizeof(char) * (pos + 1));
			if (!id)
				malloc_err(shell);
			i = -1;
			while (pos >= ++i)
				id[i] = cmd[i];
			id[i] = '\0';
			pos = id_checker(id, shell, j);
			if (!pos)
				shell->env = add_to_env(shell, cmd, id);
			free(id);
		}
		else if (ft_strchr(cmd, '+') || ft_strchr(cmd, '-'))
			nv_id(shell, shell->command->cmd[j], 1);
	}
	if (j == 1)
		export_no_args(shell);
	shell->end_type = pos;
	return (1);
}
