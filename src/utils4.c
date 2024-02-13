/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:14:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/13 19:20:35 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_print_cmd(char **command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		printf("cmd%d: %s\n", i, command[i]);
	}
}

void	free_dp(char **str, char *s1)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	free(s1);
}

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
