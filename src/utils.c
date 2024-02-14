/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:24:52 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/14 18:11:48 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*
	This function prints the saved tokens with their values, types and memory
	addresses.
*/

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

/*
	This function, which is the second part of the join_subt function, appends
	the whitespace character to the string and adds the new token to the list
	of tokens.
*/

void	join_subt2(t_token *token, char **str, t_token **new, t_shell *shell)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (!ft_isspace(token->str[i]) || token->type != T_STR)
			*str = addstr(*str, token->str[i]);
		else
		{
			add_new_token(new, str, shell);
			while (ft_isspace(token->str[i + 1]))
				i++;
		}
	}
}
