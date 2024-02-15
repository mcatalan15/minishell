/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:33:27 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/15 10:35:23 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	This function returns the type of the token by examining the first
	character of the string and returning the corresponding type value.
*/

int	get_type(char *str)
{
	if (!str[0])
		return (T_NULL);
	if (str[0] == '<' && str[1] != '<')
		return (T_REDIN);
	if (str[0] == '>' && str[1] != '>')
		return (T_REDOUT);
	if (str[0] == '<' && str[1] == '<')
		return (T_DIN);
	if (str[0] == '>' && str[1] == '>')
		return (T_DOUT);
	if (str[0] == '$' && str[1])
		return (T_DOLLAR);
	if (str[0] == '|')
		return (T_PIPE);
	return (T_STR);
}

/*
	This function calculates the number of pipes in a list of tokens, allocates
	memory for the pid array and returns a pointer to the array.
*/

int	*get_pid(t_token *token)
{
	int	len;
	int	*pid;

	len = 1;
	while (token)
	{
		if (token->type == T_PIPE)
			len++;
		token = token->next;
	}
	pid = malloc((len + 1) * sizeof(int));
	if (!pid)
		return (NULL);
	pid[len] = -1;
	return (pid);
}
