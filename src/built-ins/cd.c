/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:36:28 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/04 09:52:03 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function behaves like the 'cd' command in a shell. It searches to
	determine if the directory exists and whether it is not a directory.
	Additionally, it checks if the user has the necessary permissions to
	access the directory.
*/

int	my_cd(t_shell *shell)
{
	char	*dir;
	int		value;

	value = 0;
	dir = shell->command->cmd[1];
	value = chdir(dir);
	if (!access(dir, F_OK) && value == -1 && dir)
	{
		if (access(dir, X_OK) == -1)
			return (perm_den2(shell, dir));
	}
	else if (value == -1 && dir)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		shell->end_type = 1;
		return (0);
	}
	shell->end_type = 0;
	return (1);
}
