/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:33:27 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/06 09:28:07 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function returns the current working directory and appends the prompt
	character at the end of the string for printing.
*/

char	*get_cwd2(t_shell *shell, char *cwd_s, char *cwd)
{
	size_t	len;

	len = 0;
	len = ft_strlen(cwd);
	cwd_s = malloc(len + 3);
	if (cwd_s != NULL)
	{
		ft_strcpy(cwd_s, cwd);
		ft_strcat(cwd_s, "$ ");
	}
	else
		malloc_err(shell);
	return (cwd_s);
}

/*
	This function returns the current working directory and appends the prompt
	character at the end of the string for printing. If the getcwd function
	fails, it returns the previous working directory.
*/

char	*get_cwd(t_shell *shell)
{
	char	cwd[1024];
	char	*cwd_string;

	cwd_string = getcwd(cwd, sizeof(cwd));
	if (cwd_string != NULL)
		cwd_string = get_cwd2(shell, cwd_string, cwd);
	else
	{
		cwd_string = malloc(ft_strlen(shell->cwd) + 3);
		if (cwd_string != NULL)
			ft_strcpy(cwd_string, shell->cwd);
		else
			malloc_err(shell);
	}
	free(shell->cwd);
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
		malloc_err(token->shell);
	pid[len] = -1;
	return (pid);
}
