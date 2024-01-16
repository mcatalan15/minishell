
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

char	*parsing(char *str)
{

	return (str);
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
	char	*str;
	// char	**s;
	// int		i;
	t_shell	shell;

	(void)env;
	using_history();
	main_args(argc, argv);
	while (1)
	{
		str = readline(BLUE"minishell> "RESET);
		handle_history(str);
		init_vars(str, &shell);
		// i = 0;
		// while(s[i] != NULL)
		// 	printf("%s\n", s[i++]);

		free(str);
	}
	clear_history();
}
