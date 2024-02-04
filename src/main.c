/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/02/04 21:51:19 by mcatalan@st      ###   ########.fr       */
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
			break ;
		//  if (!ft_is_enter(str))
		// {
		init_vars(str, &shell);
		shell_program(&shell);
		free_prompt(str, cwd);
		// }
	}
	printf("exit\n");
	rl_clear_history();
	clear_program(&shell, 0, 1);
}
