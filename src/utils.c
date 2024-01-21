/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:24:52 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/21 19:56:01 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isoperate(int flag)
{
	if ((flag >= T_REDIN && flag <= T_DOUT) || flag == T_PIPE)
		return (1);
	return (0);
}

int	ft_issquote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	ft_isdquote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

void	ft_print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("value: %s type: %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
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
