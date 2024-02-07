/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:33:08 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/07 11:33:27 by mcatalan         ###   ########.fr       */
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
			len = 0;
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
