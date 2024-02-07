/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/07 12:48:54 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand(t_token *token, char **env, char *str, int pos)
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
		join_subt2(token, &str, &new, shell);
		token = token->next;
	}
	if (str || !new)
		add_new_token(&new, &str, shell);
	while (new->prev)
		new = new->prev;
	return (new);
}

t_token	*split_expansion(t_token *token, char flag, int *p, char **env)
{
	int		i;
	int		len;
	char	*s;
	int		type;

	i = *p;
	len = 0;
	type = get_type2(flag, p, &len);
	while (token->str[*p] && ((flag && token->str[*p] != flag) || \
	((!flag && token->str[*p] != '\"' && token->str[*p] != '\''))))
	{
		len++;
		(*p)++;
	}
	if (type == T_STR)
		(*p)--;
	s = ft_substr(token->str, i, len);
	if (!s)
		return (NULL);
	token = token_new(s, type, token->shell);
	if (flag)
		remove_quotes(token->str, flag);
	return (get_token(token, env));
}

t_token	*expanding(t_token *token, char **env)
{
	t_token	*aux;
	t_token	*next;

	next = NULL;
	aux = NULL;
	aux = add_subtokens(token, aux, next, env);
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
