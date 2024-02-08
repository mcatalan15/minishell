/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:33:27 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/08 20:09:20 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_expansion(char *sub, char *exp)
{
	char	*str;

	str = ft_strjoin(sub, exp);
	free(sub);
	free(exp);
	return (str);
}

int	ft_quoted_closed(char *str)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !quote)
			quote = str[i];
		else if (str[i] == '\"' && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
	}
	if (!quote)
		return (0);
	return (1);
}

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

char	*get_cwd(void)
{
	char	cwd[1024];
	char	*cwd_string;

	cwd_string = malloc(strlen(getcwd(cwd, sizeof(cwd))) + 3);
	strcpy(cwd_string, getcwd(cwd, sizeof(cwd)));
	strcat(cwd_string, "$ ");
	return (cwd_string);
}

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
