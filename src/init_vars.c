/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:57 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/15 12:47:31 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int  get_type(char *str)
// {
//     if (str[0] == ' ' && !str[1])
//         return (2);
//     if (ft_strchr(str, '\"'))
//         return (3);
//     if (ft_strchr(str, '\''))
//         return (4);
//     if (str[0] == '>' && !str[1])
//         return (5);
//     if (str[0] == '<' && !str[1])
//         return (6);
//     if (str[0] == '>' && str[1] == '>')
//         return (7);
//     if (str[0] == '<' && str[1] == '<')
//         return (8);
//     if (str[0] == '|' && !str[1])
//         return (9);
//     if (str[0] == '\$' && !str[1])
//         return (10);
//     return (1);
// }

// static t_token *token_new(char *str, int type)
// {
//     t_token *token;

//     token = malloc(sizeof(t_token));
//     if (!token)
//         return (NULL);
//     token->str = str;
//     token->type = type;
//     token->next = NULL;
//     token->prev = NULL;
//     return (token);
// }

// static void    put_tokens(t_token *token, char *str)
// {
//     char   **split;
//     int       i;

//     i = -1;
//     split = ft_split(str, ' ');
//     if (!split)
//     while (split[++i])
//     {
//     }
// }

// int init_vars(char *line, t_shell *shell)
// {
//     char    **split;
    
//     split = ft_split_shell(NULL, line, '|');
// }