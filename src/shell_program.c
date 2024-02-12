/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/12 13:00:17 by mcatalan         ###   ########.fr       */
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
			else
				kill_all_quotes(aux->str);
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

int	exec_program(t_shell *shell)
{
	t_token	*aux;
	t_token	*list;
	int		status;

	aux = shell->command->token;
	shell->command->in_copy = dup(0);
	shell->command->out_copy = dup(1);
	//ft_print_tokens(aux);
	while (aux)
	{
		list = aux;
		while (aux->type != T_PIPE && aux->next)
			aux = aux->next;
		if (aux->type == T_PIPE)
		{
			if (pipe(shell->command->fd) == -1)
				return (0);
			dup2(shell->command->fd[1], 1);
		}
		shell->command->pid = fork();
		if (!shell->command->pid)
			exec_cmd(shell, list);
		if (aux->type == T_PIPE)
		{
			dup2(shell->command->fd[0], 0);
			close(shell->command->fd[1]);
			close(shell->command->fd[0]);
		}
		aux = aux->next;
	}
	dup2(shell->command->in_copy, 0);
	dup2(shell->command->out_copy, 1);
	waitpid(shell->command->pid, &status, 0);
	if (WIFEXITED(status))
		shell->end_type = WEXITSTATUS(status);
	return (1);
}

int	shell_program(t_shell *shell, char *str)
{
	init_vars(str, shell);
	if (!parsing(shell))
		return (0);
	expansion(shell);
	exec_program(shell);
	// ft_print_tokens(shell->command->token);
	return (1);
}
