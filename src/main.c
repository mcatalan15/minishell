/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/29 10:35:08 by mcatalan         ###   ########.fr       */
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

void	free_prompt(char *str, char *cwd)
{
	free(str);
	free(cwd);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*str;
	char	*cwd;

	shell.env = env;
	using_history();
	main_args(argc, argv);
	while (1)
	{
		cwd = get_cwd();
		str = readline(cwd);
		handle_history(str);
		if (!ft_strcmp(str, "exit"))
		{
			free(str);
			break ;
		}
		init_vars(str, &shell);
		shell_program(&shell);
		free_prompt(str, cwd);
	}
	printf("exit\n");
	clear_history();
	clear_program(&shell, 0, 1);
}
