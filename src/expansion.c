/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/31 12:55:33 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expand(t_token *token, char **env, char *str, int pos)
{
	int		i;
	char	*exp;
	char	*tmp;
	int		len;
	char	*frees;

	len = 0;
	exp = NULL;
	str++;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	i = -1;
	tmp = ft_substr(--str, 0, len + 1);
	while (env[++i])
	{
		if (str[1] == '?')
			break ;
		if (!ft_strcmpc(env[i], tmp + 1, '='))
		{
			len = 0;
			exp = ft_strchr(env[i], '=') + 1;
			while (exp[len])
				len++;
			exp = ft_substr(exp, 0, len);
			break ;
		}
	}
	frees = token->str;
	if (!env[i])
	{
		exp = ft_strdup("\0");
		len = 0;
	}
	token->str = get_expansion(ft_substr(token->str, 0, pos),
			ft_strswap(str, tmp, exp));
	// printf("str: %s  tmp: %s  exp: %s\n", token->str, tmp, exp);
	free(frees);
	free(tmp);
	free(exp);
	return (len);
}

// static t_token	*add_token(t_token *token, char *str)
// {
// 	ft_print_tokens(token);
//     (void)str;
//     return (token);
// }

// static t_token	*join_subtokens(t_token *token)
// {	
// 	return (token);
// }

static void	remove_quotes(char *str, char f)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != f)
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i + 1])
	{
		str[i] = str[i + 2];
		str[i + 1] = str[i + 2];
		i++;
	}
}

static t_token	*split_expansion(t_token *token, char flag, int *p, char **env)
{
	int		i;
	int		len;
	char	*s;
	int		type;

	i = *p;
	len = 0;
	type = T_STR;
	if (flag == '\"')
		type = T_DQUOTE;
	else if (flag == '\'')
		type = T_SQUOTE;
	if (type != T_STR)
	{
		(*p)++;
		len += 2;
	}
	while (token->str[*p] && ((flag && token->str[*p] != flag) || \
	((!flag && token->str[*p] != '\"' && token->str[*p] != '\''))))
	{
		len++;
		(*p)++;
	}
	if (type == T_STR)
		(*p)--;
	s = ft_substr(token->str, i, len);
	token = token_new(s, type);
	if (flag)
		remove_quotes(token->str, flag);
	i = -1;
	while (token->str[++i] && token->type != T_SQUOTE)
	{
		if (token->str[i] == '$')
			i += expand(token, env, &token->str[i], i) - 1;
	}
	return (token);
}

t_token	*expanding(t_token *token, char **env)
{
	int		i;
	t_token	*aux;
	t_token	*next;

	next = NULL;
	aux = NULL;
	i = -1;
	while (token->str[++i])
	{
		//printf("f: %c	pos: %d", token->str[i], i);
		if (token->str[i] == '\"')
			next = split_expansion(token, '\"', &i, env);
		else if (token->str[i] == '\'')
			next = split_expansion(token, '\'', &i, env);
		else
			next = split_expansion(token, '\0', &i, env);
		// printf("next:%s	i: %d\n",next->str, i);
		if (!aux)
		{
			aux = next;
			aux->prev = NULL;
		}
		else
		{
			aux->next = next;
			next->prev = aux;
		}
		aux = next;
		next = next->next;
	}
	while (aux->prev)
		aux = aux->prev;
	ft_print_tokens(aux);
	return (token);
}
