/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/23 13:13:24 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux->next)
	{
		if (ft_isoperate(aux->type) && aux->type == aux->next->type)
			stx_erro(shell, 1, *aux->next->str);
			//exit_
		if (ft_isoperate(aux->type) && ft_isoperate(aux->next->type) \
		&& ft_isoperate(aux->type) != T_PIPE)
			stx_erro(shell, 1, *aux->next->str);
			//exit
		aux = aux->next;
	}
	if (ft_isoperate(aux->type) && !aux->next)
		stx_erro(shell, 1, '\n');
		// printf("Syntax error: syntax error near unexpected token `newline'\n");
}

void	shell_program(t_shell *shell)
{
	parsing(shell);
}
