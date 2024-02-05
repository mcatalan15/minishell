/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:51:38 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/05 18:53:20 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_is_interrogant(char *end_type, int *len)
{
	*len = 0;
	while (end_type[*len])
		(*len)++;
	return (end_type);
}

void	remove_quotes(char *str, char f)
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

char	*addstr(char *str, char c)
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
