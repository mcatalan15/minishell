/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:28:59 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/16 19:03:56 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_builtins(t_shell *shell, int built_type)
{
	if (built_type == ECHO)
		my_echo(shell);
	else if (built_type == EXPORT)
		my_export(shell);
	else if (built_type == UNSET)
		my_unset(shell);
	else if (built_type == ENV)
		my_env(shell);
	else if (built_type == CD)
		my_cd(shell);
	else if (built_type == PWD)
		my_pwd(shell);
	else if (built_type == EXIT)
		my_exit(shell);
}
