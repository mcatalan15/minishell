/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/18 12:50:17 by mcatalan@st      ###   ########.fr       */
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
	if (ft_strcmp(str, "exit") == 0)
		exit(0);
	add_history(str);
}

char	*get_cwd(void)
{
	char	cwd[1024];
	char	*colored_cwd;

	colored_cwd = malloc(ft_strlen(BLUE)
			+ ft_strlen(getcwd(cwd, sizeof(cwd)))
			+ ft_strlen(RESET) + 3);
	ft_strcpy(colored_cwd, BLUE);
	ft_strcat(colored_cwd, getcwd(cwd, sizeof(cwd)));
	ft_strcat(colored_cwd, RESET);
	ft_strcat(colored_cwd, "$");
	ft_strcat(colored_cwd, " ");
	return (colored_cwd);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*str;

	(void)env;
	using_history();
	main_args(argc, argv);
	while (1)
	{
		str = readline(get_cwd());
		handle_history(str);
		init_vars(str, &shell);
		free(str);
	}
	clear_history();
}
