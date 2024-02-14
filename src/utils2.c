/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:33:27 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 18:23:49 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function concatenates the expansion with the substring and returns
	the resulting string. Additionally, it frees the memory allocated for both
	the substring and the expansion.
*/

char	*get_expansion(char *sub, char *exp)
{
	char	*str;

	str = ft_strjoin(sub, exp);
	free(sub);
	free(exp);
	return (str);
}

/*
	This function checks if the given string is enclosed by quotes. It does so
	by comparing the quote character. It returns 0 if the string is closed and
	1 if it is not.
*/

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
	This function returns the current working directory and appends the prompt
	character at the end of the string for printing.
*/

char	*get_cwd(void)
{
	char	cwd[1024];
	char	*cwd_string;

	cwd_string = malloc(strlen(getcwd(cwd, sizeof(cwd))) + 3);
	strcpy(cwd_string, getcwd(cwd, sizeof(cwd)));
	strcat(cwd_string, "$ ");
	return (cwd_string);
}

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
