/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/06 11:35:44 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expansion(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux)
	{
		if ((aux->type == T_DOLLAR || aux->type == T_STR))
		{
			if (!aux->prev)
			{
				shell->command->token = expanding(aux, shell->env);
				while (shell->command->token->prev)
					shell->command->token = shell->command->token->prev;
			}
			else if (aux->prev->type != T_DOUT)
				aux = expanding(aux, shell->env);
		}
		aux = aux->next;
	}
	return (1);
}

static int	parsing(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux->next)
	{
		if (ft_isoperate(aux->type) && aux->type == aux->next->type)
			return (stx_erro(shell, *aux->next->str));
		if (ft_isoperate(aux->type) && ft_isoperate(aux->next->type) \
		&& ft_isoperate(aux->type) != T_PIPE)
			return (stx_erro(shell, *aux->next->str));
		aux = aux->next;
	}
	if (ft_quoted_closed(aux->str))
		return (stx_erro(shell, '\"'));
	if (ft_isoperate(aux->type) && !aux->next)
		return (stx_erro(shell, '\n'));
	return (1);
}

int	shell_program(t_shell *shell, char *str)
{
	init_vars(str, shell);
	if (!parsing(shell))
		return (0);
	expansion(shell);
	ft_print_tokens(shell->command->token);
	return (1);
}
