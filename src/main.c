/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/29 10:07:37 by mcatalan         ###   ########.fr       */
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
		exit(0);
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
	This is the main function of the program.
*/

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = envdup(env);
	shell.end_type = 0;
	shell.cwd = NULL;
	using_history();
	main_args(argc, argv);
	while (1)
	{
		wait_signal(PROMPT);
		shell.cwd = get_cwd(&shell);
		// shell.cwd = "minishell$ ";
		shell.str = readline(shell.cwd);
		update_signal(&shell);
		// if (!shell.str)
		// {
		// 	if (isatty(STDIN_FILENO))
		// 		write(2, "exit\n", 6);
		// 	exit(clear_program(&shell, 0, 0));
		// }
		handle_history(shell.str);
		signal(SIGINT, SIG_IGN);
		if (!ft_is_enter(shell.str))
			shell_program(&shell);
		free_prompt(&shell);
		clear_program(&shell, 0, 0);
	}
	free_prompt_all(&shell);
	rl_clear_history();
	clear_program(&shell, 0, 1);
}
