/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/26 09:10:35 by mcatalan@st      ###   ########.fr       */
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
		init_vars(str, &shell);
		shell_program(&shell);
		if (ft_strcmp(str, "exit") == 0)
			break ;
		free(str);
		free(cwd);
	}
	printf("exit\n");
	clear_history();
	clear_program(&shell, 0, 1);
}
