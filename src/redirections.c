/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:58:29 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/08 13:04:20 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    redirect(t_token *token)
{
    int type;
    
    if (token->prev)
        type = token->type;
    if (type = T_REDIN)
}
