
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

#include "../includes/minishell.h"

int main()
{
    char    *str;
    
    str = readline("enter some shit: ");
    printf("%s\n", str);
	free(str);
}

// void	print_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argv;
// 	if (argc == 1)
// 	{
// 		print_env(env);
// 	}
// 	else
// 	{
// 		perror("Error: to many arguments\n");
// 		exit(1);
// 	}
// }
