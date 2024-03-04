/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:51:38 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/03 20:32:24 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function appends a character to the string and returns the new
	string, freeing the memory of the old string.
*/

char	*addstr(char *str, char c, t_shell *shell)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new)
		malloc_err(shell);
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}

/*
	This function creates and initializes a new token, then returns it.
	It allocates memory for the token and sets the values of the string, type,
	shell, next, and prev members.
*/

t_token	*token_new(char *str, int type, t_shell *shell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		malloc_err(shell);
	token->str = str;
	token->type = type;
	token->shell = shell;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/*
	This function iterates through the tokens until a pipe is found. Then, it
	checks if the previous token is a redirection and if the current token is
	a string. If both conditions are met, it returns the length of the command.
*/

int	cmdlen(t_token *aux)
{
	int	len;

	len = 0;
	while (aux && aux->type != T_PIPE)
	{
		if ((!aux->prev || !ft_isrd(aux->prev->type)) && aux->type == T_STR)
			len++;
		aux = aux->next;
	}
	return (len);
}

/*
	This function searches for the path of the command and returns it.

	- If the command is not found, it prints an error message and returns NULL.
	- If the command is found but the user does not have permission to execute
		it, it prints an error message and returns NULL.
	- If the command is found and the user has permission to execute it, it
		returns the path of the command.
*/

char	*search_path2(t_shell *shell, char **split, char *path, char *add)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		path = ft_strjoin(split[i], add);
		if (!path)
			malloc_err(shell);
		if (!access(path, F_OK))
		{
			free_dp(split, add);
			if (access(path, X_OK) == -1)
			{
				free(path);
				perm_den(shell, shell->command->cmd[0]);
			}
			return (path);
		}
		free(path);
	}
	return (NULL);
}

char	*search_path(t_shell *shell, char **split)
{
	int		i;
	char	*path;
	char	*add;
	char	*cmd_no_dot;

	i = -1;
	add = NULL;
	path = NULL;
	cmd_no_dot = shell->command->cmd[0] + 1;
	if (*shell->command->cmd[0])
	{
		add = ft_strjoin("/", shell->command->cmd[0]);
		if (!add)
			malloc_err(shell);
		path = search_path2(shell, split, path, add);
		if (path)
			return (path);
	}
	free_dp(split, add);
	if (!ft_strncmp(shell->command->cmd[0], "./", 2))
		return (ft_strjoin(get_pwd(shell), cmd_no_dot));
	cmd_nf(shell, shell->command->cmd[0]);
	return (NULL);
}
