/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:28:59 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/14 10:37:32 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_builtins(t_shell *shell, int built_type)
{
    dprintf(shell->command->out_copy, "is built_in\n");
    (void)built_type;
}
