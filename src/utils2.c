/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:33:27 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/28 18:16:57 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ft_quoted_closed(char *str)
// {
// 	int		i;
// 	char	quote;

// 	i = 0;
// 	quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && !quote)
// 			quote = str[i];
// 		else if (str[i] == '\"' && !quote)
// 			quote = str[i];
// 		else if (str[i] == quote)
// 			quote = '\0';
// 		i++;
// 	}
// 	if (quote == '\0')
// 		return (0);
// 	return (1);
// }

int	clear_program(t_shell *shell, int type, int flag)
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
	if (flag)
		exit(type);
	return (0);
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
