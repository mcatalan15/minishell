/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:24:52 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/17 19:12:25 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	exit_program(t_shell *shell, int type)
// {
// 	while (shell->tokens)
// 	{
// 		free(shell->tokens->str);
// 		shell->tokens = shell->tokens->next;
// 		free(shell->tokens->prev);
// 	}

// 	while(shell)
// 	{
// 		free(shell->path);
// 		free(shell);
// 		shell = shell->next;
// 	}
// }

void	ft_print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("value: %s type: %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}
