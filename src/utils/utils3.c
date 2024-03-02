/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:39:08 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 13:20:38 by mcatalan         ###   ########.fr       */
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
	new_env = NULL;
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
	}/////////////// revisar caso err malloc (salir de mini?)
	new_env[i] = NULL;
	return (new_env);
}
