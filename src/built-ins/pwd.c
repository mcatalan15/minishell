/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:28 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/18 12:36:33 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
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
	str = get_pwd();
	printf("%s\n", str);
}
