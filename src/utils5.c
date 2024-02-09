/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:01:38 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/09 13:10:47 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

int	ft_isbuiltin(char *cmd)
{
	if (!ft_strcmpnks(cmd, "echo") || !ft_strcmpnks(cmd, "export"))
		return (1);
	if (!ft_strcmpnks(cmd, "unset") || !ft_strcmpnks(cmd, "env"))
		return (1);
	if (!ft_strcmpnks(cmd, "cd") || !ft_strcmpnks(cmd, "pwd"))
		return (1);
	return (0);
}
