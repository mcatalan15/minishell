/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:33:08 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/03 19:55:31 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skipped(char *str)
{
	int	len;

	len = 0;
	if (str[0] == '?' || ft_isdigit(str[0]))
		len++;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_') \
	&& str[0] != '?' && !ft_isdigit(str[0]))
		len++;
	return (len);
}

char	*skipped2(char **env, char *str, char *tmp)
{
	int		i;
	int		len;
	char	*exp;

	i = -1;
	len = 0;
	while (env[++i])
	{
		if (str[1] == '?' || ft_isdigit(str[1]))
			break ;
		if (!ft_strcmpc(env[i], tmp + 1, '='))
		{
			exp = ft_strchr(env[i], '=') + 1;
			while (exp[len])
				len++;
			exp = ft_substr(exp, 0, len);
			break ;
		}
	}
	if (!env[i] || ft_isdigit(str[1]))
		exp = ft_strdup("\0");
	return (exp);
}

int	get_type2(char flag, int *p, int *len)
{
	int	type;

	type = T_STR;
	if (flag == '\"')
		type = T_DQUOTE;
	else if (flag == '\'')
		type = T_SQUOTE;
	if (type != T_STR)
	{
		(*p)++;
		*len += 2;
	}
	return (type);
}

t_token	*get_token(t_token *token, char **env)
{
	int	i;

	i = -1;
	while (token->str[++i] && token->type != T_SQUOTE)
	{
		if (token->str[i] == '$')
			i += expand(token, env, &token->str[i], i) - 1;
	}
	if (!*token->str && token->type == T_STR)
	{
		free(token->str);
		token->str = NULL;
	}
	return (token);
}

t_token	*add_subtokens(t_token *token, t_token *aux, t_token *next, char **env)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == '\"')
			next = split_expansion(token, '\"', &i, env);
		else if (token->str[i] == '\'')
			next = split_expansion(token, '\'', &i, env);
		else
			next = split_expansion(token, '\0', &i, env);
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
	return (aux);
}
