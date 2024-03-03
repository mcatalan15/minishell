/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:20:46 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/03 19:56:33 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function prints an error message when the number of arguments is
	more than expected and returns 1.
*/

int	too_manyargs(void)
{
	ft_putstr_fd(" too many arguments\n", 2);
	return (1);
}

/*
	This function prints an error message when the number of arguments is
	less than expected and returns 1.
*/

int	export_no_args(t_shell *shell)
{
	ft_putstr_fd("arguments needed\n", 2);
	shell->end_type = 1;
	return (1);
}

/*
	This function prints an error message when a command has a file but is a
	directory. It returns 126.
*/

int	is_dir(t_shell *shell, DIR *dir)
{
	ft_putstr_fd(" is a directory\n", 2);
	(void)dir;
	shell->end_type = 126;
	closedir(dir);
	return (clear_program(shell, 126, 1));
}

// int	nv_id2(t_shell *shell, char *cmd, int type)
// {
// 	dup2(2, 1);
// 	printf("minishell: export: `%s': not a valid identifier\n", cmd);
// 	dup2(shell->command->out_copy, 1);
// 	(void)type;
// 	shell->end_type = 1;
// 	return (1);
// }