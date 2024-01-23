/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:04:55 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/23 13:16:40 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	stx_erro(t_shell *shell, int type, char c)
{
    dup2(2, 1);
    if (c == '\n')
        printf("Syntax error: syntax error near unexpected token `%c%c'\n", '\\', 'n');
	else
    	printf("Syntax error: syntax error near unexpected token `%c'\n", c);
    exit_program(shell, type);
}


void	rdir_erro(int type)
{
	(void)type;
}

void	exec_erro(int type)
{
	(void)type;
}