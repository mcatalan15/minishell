/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:01:59 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/02 12:27:02 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function takes an identifier as input and checks if all characters in
	the identifier are alphanumeric and lowercase. If the identifier is valid,
	it returns 0. Otherwise, it raises a 'not valid id' error.
*/

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

/*
	This function inserts the command (id=value) at the correct position in the
	environment. It iterates through the environment until it finds an id with
	an equal value (to update the command) or a larger value (to add the command
	to a new position in the environment).
*/

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

/*
	This function adds a new environment variable (cmd) to the shell's
	environment at the specified position known by comparing the identifier
	using the iter_env function.
*/

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

/*
*/

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
