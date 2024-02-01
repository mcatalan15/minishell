/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/01 11:26:19 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expansion(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux)
	{
		if ((aux->type == T_DOLLAR || aux->type == T_STR)) //-> quitar caso << D_OUT
			expanding(aux, shell->env);
		//ft_print_tokens(aux);
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
	//ft_print_tokens(shell->command->token);
	return (1);
}
