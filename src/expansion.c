/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/29 13:29:45 by mcatalan         ###   ########.fr       */
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
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_') \
	&& str[0] != '?')
		len++;
	if (str[0] == '?')
		len++;
	i = -1;
	tmp = ft_substr(--str, 0, len + 1);
	while (env[++i])
	{
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
	token->str = get_expansion(ft_substr(token->str, 0, pos), ft_strswap(str, tmp, exp));
	// printf("str: %s  tmp: %s  exp: %s\n", token->str, tmp, exp);
	free(frees);
	free(tmp);
	free(exp);
	return (len);
}

// static t_token	*add_token(t_token *token, char *str)
// {
// 	t_token	*aux;

// 	aux = token;
// 	ft_print_tokens(token);
// }

// static t_token	*split_tokens(t_token *token)
// {
// 	t_token	*aux;

// 	aux = token;
// 	token = put_tokens(token, token->str);
// 	while (token->next)
// 		token = token->next;
// 	token->next = aux->next;
// 	while (token->prev)
// 		token = token->prev;
// 	if (aux->prev)
// 		aux->prev->next = token;
// 	token->prev = aux->prev;
// 	aux->prev = NULL;
// 	aux->next = NULL;
// 	// free(aux); // -> error
// 	// ft_print_tokens(token);
// 	return (token);
// }

static int	remove_quotes(char *str, int pos)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != str[pos])
		i++;
	while (str[i] && i + 1 != pos)
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i])
	{
		str[i] = str[i + 2];
		str[i + 1] = str[i + 2];
		i++;
	}
	return (2);
}

// static t_token	*split_expansion(t_token *token)
// {
// 	t_token	*aux;
// 	int		i;

// 	aux = token;
// 	i = 0;
// 	while (aux->str[i])
// 	{
// 		if (aux->type == T_DQUOTE)
// 			printf("is_double_quote\n");
// 		if (aux->type == T_STR)
// 			printf("is_string\n");
// 		if (aux->type == T_DOLLAR)
// 			printf("is_expansion\n");
// 		i++;
// 	}
// 	printf("split: %s\n", aux->str);
// 	return (token);
// }

t_token	*expanding(t_token *token, char **env)
{
	int		i;
	char	f;

	i = -1;
	f = '\0';
	while (token->str[++i])
	{
		// printf("position: %c\n", token->str[i]);
		if (token->str[i] == '\"' && !f)
			f = '\"';
		else if (token->str[i] == '\'' && !f)	
			f = '\'';
		else if (token->str[i] == f)
		{
			f = '\0';
			i -= remove_quotes(token->str, i);
		}
		printf("position: %d		value F: %c			char: %c\n", i, f, token->str[i]);
		if (token->str[i] == '$' && f != '\'')
		{
			printf("Entra\n");
			i += expand(token, env, &token->str[i], i) - 1;
			if (f == '\"')
				token->type = T_DQUOTE;
		}
		// split_expansion(token);
		//split
	}
	// token = split_tokens(token);
	return (token);
}
