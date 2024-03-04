/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/03 20:05:40 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function handles shell command token expansion, such as variable
	expansion and removing quotes.
*/

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
				aux = shell->command->token;
			}
			else if (aux->prev->type != T_DIN)
				aux = expanding(aux, shell->env);
			else
				kill_all_quotes(aux->str);
		}
		aux = aux->next;
	}
	return (1);
}

/*
	This function performs syntax validation on the list of tokens. It returns
	1 if the syntax is correct and 'stx_erro' if it is not.
*/

static int	parsing(t_shell *shell)
{
	t_token	*aux;

	aux = shell->command->token;
	while (aux->next)
	{
		if (ft_isoperate(aux->type) && aux->type == aux->next->type)
			return (stx_erro(shell, *aux->next->str));
		if ((ft_isoperate(aux->type) && ft_isoperate(aux->next->type) \
		&& aux->type != T_PIPE))
			return (stx_erro(shell, *aux->next->str));
		if ((aux->type == T_PIPE && !aux->prev))
			return (stx_erro(shell, *aux->str));
		aux = aux->next;
	}
	if (ft_quoted_closed(aux->str))
		return (stx_erro(shell, '\"'));
	if (ft_isoperate(aux->type) && !aux->next)
		return (stx_erro(shell, '\n'));
	return (1);
}

int	exec_program2(t_shell *shell, t_token *list, t_token *aux, int *pid_num)
{
	wait_signal(EXECUTION);
	shell->command->cmd = get_cmd(list);
	if (aux->type == T_PIPE)
	{
		if (pipe(shell->command->fd) == -1)
			return (0);
		dup2(shell->command->fd[1], 1);
	}
	if (!ft_isbuiltin(*(shell->command->cmd)) || shell->command->pid[1] != -1)
		shell->command->pid[*(pid_num)] = fork();
	if (ft_isbuiltin(*(shell->command->cmd)) && shell->command->pid[1] == -1)
	{
		if (!exec_cmd(shell, list, 1, *pid_num))
			return (0);
	}
	else if (!shell->command->pid[*(pid_num)])
		exec_cmd(shell, list, 0, *pid_num);
	(*pid_num)++;
	if (aux->type == T_PIPE)
	{
		dup2(shell->command->fd[0], 0);
		close(shell->command->fd[1]);
		close(shell->command->fd[0]);
	}
	return (1);
}

int	exec_program(t_shell *shell)
{
	t_token	*aux;
	t_token	*list;
	int		i;

	i = 0;
	aux = shell->command->token;
	shell->command->in_copy = dup(0);
	shell->command->out_copy = dup(1);
	shell->command->pid = get_pid(aux);
	if (!manage_hd(shell, shell->command->token))
		return (0);
	while (aux)
	{
		list = aux;
		while (aux->type != T_PIPE && aux->next)
			aux = aux->next;
		dup2(shell->command->out_copy, 1);
		if (!exec_program2(shell, list, aux, &i))
			return (0);
		aux = aux->next;
	}
	wait_for_children(shell, shell->command->pid);
	return (1);
}

/*
	This function initialize the tokens, parsing, expansion and the execution.
*/

int	shell_program(t_shell *shell)
{
	init_vars(shell->str, shell);
	if (!parsing(shell))
		return (0);
	expansion(shell);
	exec_program(shell);
	return (1);
}
