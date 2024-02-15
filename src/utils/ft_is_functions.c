/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_finctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:24:52 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/15 10:35:20 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function, when given a flag, checks if the value is the same as any
	other operator. The operators include the four types of redirections
	(<, >, <<, >>) and the pipe operator (|).
*/

int	ft_isoperate(int flag)
{
	if ((flag >= T_REDIN && flag <= T_DOUT) || flag == T_PIPE)
		return (flag);
	return (0);
}

/*
	Function that checks if the char is a single quote.
*/

int	ft_issquote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

/*
	Function that checks if the char is a double quote.
*/

int	ft_isdquote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

/*
	This function checks whether the character corresponds to any of the four
	redirection symbols.
*/

int	ft_isrd(int flag)
{
	if ((flag >= T_REDIN && flag <= T_DOUT))
		return (flag);
	return (0);
}

/*
	This function checks if the given string ends with a question mark!!!!!!!!!!!!!!!!!!!!!!!
*/

char	*ft_is_interrogant(char *end_type)
{
	int	len;

	len = 0;
	while (end_type[len])
		len++;
	return (end_type);
}
