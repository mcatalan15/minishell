/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:39:08 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/06 09:29:04 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function duplicates the environment and returns the new environment.
*/

char	**envdup(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
	{
		ft_putstr_fd("minishell: malloc: error in malloc\n", 2);
		exit(1);
	}
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			ft_putstr_fd("minishell: malloc: error in malloc\n", 2);
			free_dp(new_env, NULL);
			exit(1);
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

/*
	This function checks if the command is executed in the father process.
*/

int	is_father(t_shell *shell)
{
	t_token	*aux;

	if (!shell->str)
		return (1);
	aux = shell->command->token;
	while (aux)
	{
		if (aux->type == T_PIPE)
			return (0);
		aux = aux->next;
	}
	if (ft_isbuiltin(shell->command->cmd[0]))
		return (1);
	return (0);
}

/*
	This function, which is the second part of the join_subt function, appends
	the whitespace character to the string and adds the new token to the list
	of tokens.
*/

void	join_subt2(t_token *token, char **str, t_token **new, t_shell *shell)
{
	int	i;

	i = -1;
	if (!token->str)
	{
		*str = NULL;
		return ;
	}
	while (token->str[++i])
	{
		if (!ft_isspace(token->str[i]) || token->type != T_STR)
			*str = addstr(*str, token->str[i], shell);
		else
		{
			add_new_token(new, str, shell);
			while (ft_isspace(token->str[i + 1]))
				i++;
		}
	}
}

/*
	TBC
*/

void	close_pipe(t_shell *shell)
{
	dup2(shell->command->fd[0], 0);
	close(shell->command->fd[1]);
	close(shell->command->fd[0]);
}
