
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:39:21 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/11 11:14:46 by mcatalan         ###   ########.fr       */
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

char	*get_cwd()
{
	char	cwd[1024];	
	char	*colored_cwd = malloc(ft_strlen(BLUE) + ft_strlen(getcwd(cwd, sizeof(cwd))) + ft_strlen(RESET) + 3);
	strcpy(colored_cwd, BLUE);
	strcat(colored_cwd, getcwd(cwd, sizeof(cwd)));
	strcat(colored_cwd, RESET);
	strcat(colored_cwd, "$");
	strcat(colored_cwd, " ");
	return (colored_cwd);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	// char	**s;
	// int		i;
	// t_shell	shell;

	(void)env;
	using_history();
	main_args(argc, argv);
	while (1)
	{
		str = readline(get_cwd());
		handle_history(str);
		// init_vars(str, &shell);
		free(str);
	}
	clear_history();
}
