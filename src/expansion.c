/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/07 11:32:53 by mcatalan         ###   ########.fr       */
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

	exp = NULL;
	str++;
	len = skipped(str);
	i = -1;
	tmp = ft_substr(--str, 0, len + 1);
	exp = skipped2(env, str, tmp);
	len = ft_strlen(exp);
	if (str[1] == '?')
		exp = ft_is_interrogant(ft_itoa(token->shell->end_type));
	frees = token->str;
	token->str = get_expansion(ft_substr(token->str, 0, pos),
			ft_strswap(str, tmp, exp));
	free(frees);
	free(tmp);
	free(exp);
	return (len);
}

void	add_new_token(t_token **new, char **str, t_shell *shell)
{
	t_token	*aux;

	if (!*str)
	{
		*str = malloc(sizeof(char));
		*str[0] = '\0';
	}
	aux = token_new(*str, T_STR, shell);
	if (!*new)
		*new = aux;
	else
	{
		printf("entra\n");
		(*new)->next = aux;
		aux->prev = *new;
		*new = (*new)->next;
	}
	*str = NULL;
}

static t_token	*join_subtokens(t_token *token)
{
	t_token	*new;
	char	*str;
	t_shell	*shell;

	str = NULL;
	new = NULL;
	shell = token->shell;
	while (token)
	{
		join_subtoken2(token, &str, &new, shell);
		token = token->next;
	}
	if (str || !new)
		add_new_token(&new, &str, shell);
	while (new->prev)
		new = new->prev;
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

t_token	*create_and_link_tokens(t_token *current, t_token *next)
{
	if (!current)
	{
		current = next;
		current->prev = NULL;
	}
	else
	{
		current->next = next;
		next->prev = current;
	}
	return (next);
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
