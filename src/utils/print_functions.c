/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:19:06 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/17 15:16:10 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function prints the saved tokens with their values, types and memory
	addresses.
*/

void	ft_print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("value: %s type: %d mem: %p\n", tmp->str, tmp->type, tmp);
		tmp = tmp->next;
	}
}

/*
	This function prints the command.
*/

void	ft_print_cmd(char **command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		printf("cmd%d: %s mem:%p\n", i, command[i], command[i]);
	}
}

/*
	This function prints the environment.
*/

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
