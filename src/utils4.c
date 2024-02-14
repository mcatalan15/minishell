/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:14:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/14 18:45:15 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function iterates through the string until the first quote is found.
	Then, it removes the quotes from the string and returns the length of the
	modified string.
*/

void	kill_all_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += remove_quotes(&str[i], str[i]) - 1;
	}
}

/*
	This function iterates through the tokens until a pipe is found. Then, it
	checks if the previous token is a redirection and if the current token is
	a string. If both conditions are met, it returns the length of the command.
*/

int	cmdlen(t_token	*aux)
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
	This function prints the command.
*/

void	ft_print_cmd(char **command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		printf("cmd%d: %s\n", i, command[i]);
	}
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
	This function searches for the path of the command and returns it.

	- If the command is not found, it prints an error message and returns NULL.
	- If the command is found but the user does not have permission to execute
		it, it prints an error message and returns NULL.
	- If the command is found and the user has permission to execute it, it
		returns the path of the command.
*/

char	*search_path(t_shell *shell, char **split)
{
	int		i;
	char	*path;
	char	*add;

	i = -1;
	add = ft_strjoin("/", shell->command->cmd[0]);
	while (split[++i])
	{
		path = ft_strjoin(split[i], add);
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
	free_dp(split, add);
	cmd_nf(shell, shell->command->cmd[0]);
	return (NULL);
}
