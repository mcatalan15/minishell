/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/05 14:09:05 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	redirection(t_shell *shell)
// {
// 	t_token	*aux;

// 	aux = shell->command->token;
// 	while (aux)
// 	{
// 		// if (aux->type >= 2 && aux->type <= 4)
// 		// 	redirect(aux);
// 			//redirections
// 		// else if (aux->type == T_DOUT)
// 		// 	here_doc(aux);
// 			// here doc
// 	}

// 	return (1);
// }

static int	expansion(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux)
	{
		if ((aux->type == T_DOLLAR || aux->type == T_STR)) //-> quitar caso << D_OUT
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
		aux = aux->next; //-> error
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

int	shell_program(t_shell *shell)
{
	if (!parsing(shell))
		return (0);
	expansion(shell);
	// redirection(shell);
	ft_print_tokens(shell->command->token);
	return (1);
}
