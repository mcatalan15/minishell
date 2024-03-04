/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/03/03 14:52:00 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function handles the arguments of the main function.
	In case of error, it prints an error message and exits the program.
*/

void	main_args(int argc, char **argv)
{
	if (argc != 1 || argv[1] != NULL)
	{
		printf("Error: too many arguments\n");
		exit(1);
	}
}

/*
	This function handles the history of the shell.
*/

void	handle_history(char *str)
{
	if (!str || *str == '\0')
		return ;
	add_history(str);
}

/*
	This is the main function of the program. Initialize th minishell and the
	loop to read the input.
*/

void	main_loop(t_shell *shell)
{
	while (1)
	{
		wait_signal(PROMPT);
		shell->cwd = get_cwd(shell);
		shell->str = readline(shell->cwd);
		update_signal(shell);
		handle_history(shell->str);
		if (!shell->str)
		{
			if (isatty(STDIN_FILENO))
				my_exit(shell);
			break ;
		}
		update_signal(shell);
		signal(SIGINT, SIG_IGN);
		if (!ft_is_enter(shell->str))
			shell_program(shell);
		update_signal(shell);
		free_prompt(shell);
		clear_program(shell, 0, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = envdup(env);
	shell.end_type = 0;
	shell.command = NULL;
	g_signal = 0;
	shell.cwd = NULL;
	shell.str = NULL;
	using_history();
	main_args(argc, argv);
	main_loop(&shell);
	free_prompt_all(&shell);
	rl_clear_history();
	clear_program(&shell, shell.end_type, 1);
}
