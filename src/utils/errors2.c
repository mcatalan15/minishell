/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:51:21 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/03 19:54:14 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function is used to print the error message when a command is not
	found.
*/

void	cmd_nf(t_shell *shell, char *cmd)
{
	(void)cmd;
	ft_putstr_fd(" command not found\n", 2);
	clear_program(shell, PATH_ERROR, 1);
}

/*
	This function is used to handle errors related to the redirections. It
	prints an error message and returns the end type. If the redirection error
	is related to a builtin command, it returns 0 so the program can continue.
*/

void	rdir_erro(t_shell *shell, int type, char *str)
{
	int	flag;

	flag = 1;
	if (shell->command->pid[1] == -1 && ft_isbuiltin(str))
		flag = 0;
	ft_putstr_fd("Redirection error\n", 2);
	shell->end_type = 1;
	clear_program(shell, type, flag);
}

/*
	This function is used to print error message when the id given for export
	is not valid.
*/

int	nv_id(t_shell *shell, char *cmd, int type)
{
	(void)cmd;
	ft_putstr_fd(" not a valid identifier\n", 2);
	(void)type;
	shell->end_type = 1;
	return (1);
}

/*
	This function is used when a malloc error occurs. It prints an error
	message and returns with EXIT_FAILURE.
*/

int	malloc_err(t_shell *shell)
{
	ft_putstr_fd("error in malloc\n", 2);
	shell->end_type = 1;
	return (clear_program(shell, EXIT_FAILURE, 0));
}

/*
	This function is used to handle errors related to the exit command. If the
	exit command is executed with more than one argument or with non-numerical
	characters, it prints an error message and returns 255. If the exit command
	is successful, it returns the number of the argument given.
*/

int	num_argre(t_shell *shell)
{
	ft_putstr_fd(" numeric argument required\n", 2);
	free_dp(shell->env, NULL);
	clear_program(shell, 255, 1);
	return (0);
}
