/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:50:14 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/26 12:52:09 by mcatalan         ###   ########.fr       */
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

	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_') \
	&& str[0] != '?')
		len++;
	if (str[0] == '?')
		len++;
	i = -1;
	tmp = ft_substr(str, 0, len);
	while (env[++i])
	{
		if (!ft_strcmpc(env[i], tmp, '='))
		{
			exp = tmp;
			tmp = ft_strjoin("$", tmp);
			free(exp);
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
	printf("%s\n", token->str);
	free(str);
	free(tmp);
	free(exp);
}

void	expanding(t_token *token, char **env)
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
			expand(token, env, &token->str[i + 1]);
		//remove qoutes
		//split
	}
}
