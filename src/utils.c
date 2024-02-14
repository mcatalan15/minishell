/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:24:52 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/14 13:00:12 by mcatalan         ###   ########.fr       */
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

int	ft_isrd(int flag)
{
	if ((flag >= T_REDIN && flag <= T_DOUT))
		return (flag);
	return (0);
}

char	*ft_is_interrogant(char *end_type)
{
	int	len;

	len = 0;
	while (end_type[len])
		len++;
	return (end_type);
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
