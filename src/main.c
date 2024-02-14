/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/14 13:12:17 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	main_args(int argc, char **argv)
{
	if (argc != 1 || argv[1] != NULL)
	{
		printf("Error: to many arguments\n");
		exit(0);
	}
}

void	handle_history(char *str)
{
	if (!str || *str == '\0')
		return ;
	add_history(str);
}

void	free_prompt(t_shell *shell)
{
	free(shell->str);
	free(shell->cwd);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.env = env;
	shell.end_type = 0;
	using_history();
	main_args(argc, argv);
	while (1)
	{
		shell.cwd = get_cwd();
		shell.str = readline(shell.cwd);
		handle_history(shell.str);
		if (!ft_is_enter(shell.str))
			shell_program(&shell);
		free_prompt(&shell);
		clear_program(&shell, 0, 0);
	}
	free_prompt(&shell);
	rl_clear_history();
	clear_program(&shell, 0, 1);
}
