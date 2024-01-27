/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/27 20:13:15 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand(t_token *token, char **env, char *str)
{
	int		i;
	char	*exp;
	char	*tmp;
	int		len;

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
	str = token->str;
	if (!env[i])
		exp = ft_strdup("\0");
	token->str = ft_strswap(str, tmp, exp);
	// printf("str: %s  tmp: %s  exp: %s\n", token->str, tmp, exp);
	free(str);
	free(tmp);
	free(exp);
}

static t_token	*split_tokens(t_token *token)
{
	t_token	*aux;

	aux = token;
	token = put_tokens(token, token->str);
	while (token->next)
		token = token->next;
	token->next = aux->next;
	while (token->prev)
		token = token->prev;
	if (aux->prev)
		aux->prev->next = token;
	token->prev = aux->prev;
	aux->prev = NULL;
	aux->next = NULL;
	free(aux);
	return (token);
}

t_token	*expanding(t_token *token, char **env)
{
	int		i;
	char	f;

	i = -1;
	f = '\0';
	while (token->str[++i])
	{
		if (token->str[i] == '\"' && !f)
			f = '\"';
		else if (token->str[i] == '\'' && !f)
			f = '\'';
		else if (token->str[i] == f)
			f = '\0';
		if (token->str[i] == '$' && f != '\'')
			expand(token, env, &token->str[i]);
		//remove qoutes
		//split
	}
	token = split_tokens(token);
	return (token);
}
