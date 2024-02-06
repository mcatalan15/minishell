/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:24:52 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/06 11:21:32 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isoperate(int flag)
{
	if ((flag >= T_REDIN && flag <= T_DOUT) || flag == T_PIPE)
		return (flag);
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
		printf("value: %s type: %d mem: %p\n", tmp->str, tmp->type, tmp);
		tmp = tmp->next;
	}
}
