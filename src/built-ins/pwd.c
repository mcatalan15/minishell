/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:28 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/02 12:21:32 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function retrieves the current path using the getcwd function and
	prints it as the prompt. If the minishell program is located in a
	nonexistent path and getcwd returns null, the prompt is retrieved from the
	last stored path in shell->cwd.
*/

char	*get_pwd(t_shell *shell)
{
	char	cwd[1024];
	char	*cwd_string;
	size_t	len;

	cwd_string = getcwd(cwd, sizeof(cwd));
	len = 0;
	if (cwd_string != NULL)
	{
		len = ft_strlen(cwd);
		cwd_string = malloc(len + 2);
		if (cwd_string != NULL)
			ft_strcpy(cwd_string, cwd);
		else
			malloc_err(shell);
	}
	else
	{
		cwd_string = malloc(ft_strlen(shell->cwd) + 3);
		if (cwd_string != NULL)
			ft_strcpy(cwd_string, shell->cwd);
		else
			malloc_err(shell);
	}
	return (cwd_string);
}

/*
	This function takes the path printed on the prompt as input (passed as str)
	and removes the dollar sign, which is reserved for the prompt output.
*/

char	*remove_dollar(char *str)
{
	char	*new;
	int		i;

	i = ft_strlen(str);
	if (str[i - 2] == '$')
	{
		new = malloc(i);
		if (!new)
			return (NULL); // -> malloc_err(shell);
		i = 0;
		while (str[i] && str[i] != '$')
		{
				new[i] = str[i];
				i++;
		}
		new[i] = '\0';
	}
	else
		new = ft_strdup(str);
	free(str);
	return (new);
}

/*
	This function replicates the behavior of the pwd command in Bash. It
	retrieves the current path, removes the dollar sign from the saved path,
	and prints it.
*/

void	my_pwd(t_shell *shell)
{
	char	*str;

	str = get_pwd(shell);
	str = remove_dollar(str);
	printf("%s\n", str);
	free(str);
	shell->end_type = 0;
}
