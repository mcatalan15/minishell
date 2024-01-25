/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/25 17:38:18 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expansion(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux)
	{
		if (aux->type == T_DOLLAR || aux->type == T_STR)
			expanding(aux, shell->env);
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
	if (ft_isoperate(aux->type) && !aux->next)
		return (stx_erro(shell, '\n'));
	return (1);
}

int	shell_program(t_shell *shell)
{
	if (!parsing(shell))
		return (0);
	expansion(shell);
	return (1);
}
