/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:28 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/16 11:58:59 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path(void)
{
	char	cwd[1024];
	char	*cwd_string;

	cwd_string = malloc(strlen(getcwd(cwd, sizeof(cwd))) + 3);
	strcpy(cwd_string, getcwd(cwd, sizeof(cwd)));
	return (cwd_string);
}

void	my_pwd(t_shell *shell)
{
	char	*str;

	(void)shell;
	str = get_path();
	printf("%s\n", str);
}