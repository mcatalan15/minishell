/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:33:27 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/22 12:02:59 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_program(t_shell *shell, int type)
{
	t_token	*aux;

	aux = shell->command->token;
	while (shell->command->token)
	{
		aux = aux->next;
		//printf("token->str: %p, token: %p\n",shell->command->token->str, shell->command->token);
		free(shell->command->token->str);
		free(shell->command->token);
		shell->command->token = aux;
	}
	free(shell->command);
	exit(type);
}

char	*get_cwd(void)
{
	char	cwd[1024];
	char	*cwd_string;

	cwd_string = malloc(strlen(getcwd(cwd, sizeof(cwd))) + 3);

	strcpy(cwd_string, getcwd(cwd, sizeof(cwd)));
	strcat(cwd_string, "$ ");
	return (cwd_string);
}
