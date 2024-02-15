/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_free_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:13:32 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/15 10:35:12 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function is used to clear the list of tokens. It frees the memory of
	the tokens and the strings.
*/

int	clear_list(t_token *token)
{
	t_token	*aux;

	aux = token;
	if (!aux)
		return (0);
	while (aux)
	{
		aux = aux->next;
		free(token->str);
		free(token);
		token = aux;
	}
	return (0);
}

/*
	This function is used to clear the command structure. It frees the memory
	of the command and the tokens. If the flag is set to 1, it exits the
	program with the given type.
*/

int	clear_program(t_shell *shell, int type, int flag)
{
	t_token	*aux;

	if (!shell->command)
		return (0);
	aux = shell->command->token;
	while (shell->command->token)
	{
		aux = aux->next;
		free(shell->command->token->str);
		free(shell->command->token);
		shell->command->token = aux;
	}
	free(shell->command->cmd);
	free(shell->command->path);
	free(shell->command);
	if (flag)
		exit(type);
	shell->command = NULL;
	return (0);
}

/*
	This function frees the memory of the double pointer and the string.
*/

void	free_dp(char **str, char *s1)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	free(s1);
}

/*
	This function frees the prompt.
*/

void	free_prompt(t_shell *shell)
{
	free(shell->str);
	free(shell->cwd);
}
