/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:28 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/25 21:17:23 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*get_pwd(void)
// {
// 	char	cwd[1024];
// 	char	*cwd_string;

// 	cwd_string = malloc(strlen(getcwd(cwd, sizeof(cwd))) + 3);
// 	strcpy(cwd_string, getcwd(cwd, sizeof(cwd)));
// 	return (cwd_string);
// }

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

char	*remove_dollar(char *str)
{
	char	*new;
	int		i;

	i = ft_strlen(str);
	if (str[i - 2] == '$')
	{
		new = malloc(i);
		if (!new)
			return (NULL);
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

void	my_pwd(t_shell *shell)
{
	char	*str;

	str = get_pwd(shell);
	str = remove_dollar(str);
	printf("%s\n", str);
	free(str);
}
