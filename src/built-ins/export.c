/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:01:59 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/06 09:26:52 by mcatalan@st      ###   ########.fr       */
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
	if ((s[i] == '=' || !s[i]) && i != 0)
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
		if (!ft_strcmpc(id, env[i], '=') && !flag)
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
	This function iterates through the export values and check if the command
	contains an equal sign. If it does, it calls the iter_env function to add
	the command to the environment. If the command does not contain an equal
	sign, it raises a 'not valid id' error.
*/

int	iter_export(t_shell *shell, int pos, int j)
{
	char	*cmd;
	char	*id;
	int		i;

	cmd = NULL;
	id = NULL;
	cmd = shell->command->cmd[j];
	pos = ft_is_equal(cmd, pos);
	id = malloc(sizeof(char) * (pos + 1));
	if (!id)
		malloc_err(shell);
	i = -1;
	while (pos >= ++i)
		id[i] = cmd[i];
	id[i] = '\0';
	pos = id_checker(id, shell, j);
	if (ft_strchr(cmd, '='))
	{
		if (!pos)
			shell->env = add_to_env(shell, cmd, id);
	}
	free(id);
	return (pos);
}

/*
	This function is called when the export command is called. Iterates the
	command given to the export command and calls the iter_export function to
	check if the command is valid and to add it to the environment.
*/

int	my_export(t_shell *shell)
{
	int		pos;
	int		j;

	pos = 0;
	j = 0;
	while (shell->command->cmd[++j])
		pos = iter_export(shell, pos, j);
	shell->end_type = pos;
	if (j == 1)
		export_no_args(shell);
	return (1);
}
