/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:14:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/08 13:05:32 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	kill_all_quotes(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += remove_quotes(&str[i], str[i]) - 1;
	}
}

int cmdlen(t_token *aux)
{
    int len;

    len = 0;
    while (aux && aux->type != T_PIPE)
	{
		if (aux->prev && !ft_isoperate(aux->prev->type))
        len++;
	}
    return (len);
}

void	ft_print_cmd(char **command)
{
	int i;

	i = -1;
	while (command[++i])
		printf("cmd%d: %s\n", i, command[i]);
}
