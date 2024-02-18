/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:25 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/18 14:01:06 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	id_checker(char *s)
{
	int	i;

	i = 1;
	if (!ft_isdigit(s[0]))
	{
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	}
	if (s[i] == '=')
		return (0);
	else
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
		return (NULL);
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
		if (ft_strcmpc(id, env[i], '=') < 0 && !flag)
		{
			new[j++] = cmd;
			flag = 1;
			i--;
		}
		else if (!ft_strcmpc(id, env[i], '='))
			new[j++] = cmd;
		else
			new[j++] = ft_strdup(env[i]);
	}
	if (!flag)
		new[j++] = cmd;
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
		return (NULL);
	iter_env(shell->env, new, id, cmd);
	free_dp(shell->env, NULL);
	return (new);
}

int	my_export(t_shell *shell)
{
	char	**cmd;
	char	*id;
	int		i;
	int		pos;

	id = NULL;
	pos = 0;
	cmd = shell->command->cmd;
	if (!ft_strchr(cmd[1], '='))
		return (stx_erro(shell, 'a'));
	pos = ft_is_equal(cmd[1], pos);
	id = malloc(sizeof(char) * (pos + 1));
	i = -1;
	while (pos >= ++i)
		id[i] = cmd[1][i];
	id[i] = '\0';
	if (!id_checker(id))
		shell->env = add_to_env(shell, cmd[1], id);
	free(id);
	return (1);
}

//bash: export: `1A=ads': not a valid identifier
//bash: export: `=': not a valid identifier