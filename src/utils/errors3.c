/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:20:46 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/02 11:15:49 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	too_manyargs(void)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("minishell: exit: too many arguments\n");
	dup2(fd, 1);
	return (1);
}

int	export_no_args(t_shell *shell)
{
	dup2(2, 1);
	printf("minishell: export: arguments needed\n");
	dup2(shell->command->out_copy, 1);
	shell->end_type = 1;
	return (1);
}

// int	nv_id2(t_shell *shell, char *cmd, int type)
// {
// 	dup2(2, 1);
// 	printf("minishell: export: `%s': not a valid identifier\n", cmd);
// 	dup2(shell->command->out_copy, 1);
// 	(void)type;
// 	shell->end_type = 1;
// 	return (1);
// }