/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:18:52 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/16 12:18:36 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token  t_token;
typedef struct s_shell   t_shell;
typedef struct s_command    t_command;
// typedef struct s_vars
// {
//     char **path;
//     char **env;
// }t_vars;

struct  s_token
{
    char    *str;
    int     type;
    t_token *next;
    t_token *prev;
};

struct  s_command
{
    char    **cmd;
    char    *path;  
    t_token *token;  
    t_command *next;
    t_command *prev;
};

struct s_shell
{
    char    **env;
    t_command   *command;
};

/*
TYPES
1: str
2: ' '
3: "__"
4: '__'
5:  >
6:  <
7:  >>
8:  <<
9: $
*/

#endif