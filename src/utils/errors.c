/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:04:55 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/03 21:01:05 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function is used to handle syntax errors. It prints an error message
	and returns the end type.
*/

int	stx_erro(t_shell *shell, char c)
{
	(void)c;
	ft_putstr_fd("syntax error\n", 2);
	shell->end_type = STX_ERRO;
	return (clear_program(shell, STX_ERRO, 0));
}

/*
	This function is used to handle errors related to the redirections. It
	prints an error message and returns the end type. If the redirection error
	is related to a builtin command, it returns 0 so the program can continue.
*/

void	nsf_or_dir(t_shell *shell, int type, char *str)
{
	int	flag;

	(void)str;
	flag = is_father(shell);
	ft_putstr_fd(" No such file or directory\n", 2);
	shell->end_type = type;
	clear_program(shell, type, !flag);
}

/*
	This function is used to handle errors when accessing a directory. If a
	path is not found, it prints an error message and returns 127.
*/

void	nsf_or_dir2(t_shell *shell, char *str)
{
	(void)str;
	ft_putstr_fd(" No such file or directory\n", 2);
	shell->end_type = PATH_ERROR;
	clear_program(shell, PATH_ERROR, 0);
}

/*
	This function is used to handle errors when accessing a directory, file or
	executable. It prints an error message and returns 1.
*/

int	perm_den2(t_shell *shell, char *dir)
{
	int	flag;

	flag = 1;
	ft_putstr_fd(" Permission denied\n", 2);
	shell->end_type = 1;
	if (shell->command->pid[1] == -1 && ft_isbuiltin(dir))
		flag = 0;
	clear_program(shell, 1, flag);
	return (0);
}

/*
	This function is used to handle errors when accessing a directory, file or
	executable. It prints an error message and returns 126. Also use flag to
	decide if the program should continue or not depending if the command is a
	builtin.
*/

void	perm_den(t_shell *shell, char *cmd)
{
	int	flag;

	flag = 1;
	if (shell->command->pid[1] == -1 && ft_isbuiltin(cmd))
		flag = 0;
	ft_putstr_fd(" Permission denied\n", 2);
	shell->end_type = 126;
	clear_program(shell, 126, flag);
}
