/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/03 12:42:03 by mcatalan@st      ###   ########.fr       */
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
	if (str[0] == '?' || ft_isdigit(str[0]))
		len++;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_')\
	&& str[0] != '?' && !ft_isdigit(str[0]))
		len++;
	i = -1;
	tmp = ft_substr(--str, 0, len + 1);
	while (env[++i])
	{
		if (str[1] == '?' || ft_isdigit(str[1]))
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
	if (str[1] == '?')
		exp = ft_is_interrogant(ft_itoa(token->shell->end_type), &len);
	if (!env[i] || ft_isdigit(str[1]))
	{
		exp = ft_strdup("\0");
		len = 0;
	}
	token->str = get_expansion(ft_substr(token->str, 0, pos),
			ft_strswap(str, tmp, exp));
	free(frees);
	free(tmp);
	free(exp);
	return (len);
}

static char	*addstr(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}

void	add_new_token(t_token **new, t_token **tmp, char **str, t_shell *shell)
{
	t_token	*aux;

	if (!*str)
	{
		*str = malloc(sizeof(char));
		*str[0] = '\0';
	}
	aux = token_new(*str, T_STR, shell);
	if (!*new)
	{
		*new = aux;
		*tmp = *new;
	}
	else
	{
		(*new)->next = aux;
		aux->prev = *new;
		*new = (*new)->next;
	}
	*str = NULL;
}

static t_token	*join_subtokens(t_token *token)
{
	t_token	*new;
	t_token	*aux;
	char	*str;
	int		i;
	t_shell	*shell;

	str = NULL;
	new = NULL;
	aux = NULL;
	shell = token->shell;
	while (token)
	{
		i = -1;
		while (token->str[++i])
		{
			if (!ft_isspace(token->str[i]) || token->type != T_STR)
				str = addstr(str, token->str[i]);
			else
			{
				add_new_token(&new, &aux, &str, shell);
				while (ft_isspace(token->str[i + 1]))
					i++;
			}
		}
		token = token->next;
	}
	if (str || !aux)
		add_new_token(&new, &aux, &str, shell);
	new = aux;
	return (new);
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
	token = token_new(s, type, token->shell);
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
	while (aux->prev)
		aux = aux->prev;
	next = aux;
	aux = join_subtokens(aux);
	clear_list(next);
	aux->prev = token->prev;
	if (token->prev)
		token->prev->next = aux;
	while (aux->next)
		aux = aux->next;
	aux->next = token->next;
	if (token->next)
		token->next->prev = aux;
	free(token->str);
	free(token);
	token = NULL;
	return (aux);
}
