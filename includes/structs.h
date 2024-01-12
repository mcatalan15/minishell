/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:18:52 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/11 11:56:38 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token  t_token;
typedef struct s_exec   t_exec;
// typedef struct s_vars
// {
//     char **path;
//     char **env;
// }t_vars;

struct  s_token
{
    char    *str;                 //*type 1: str
    int     type;                 //*type 2: ' '
    t_token *next;                //*type 3: "__"
};                                //*type 4: '__'
                                  //*type 5:  > 
struct  s_exec                    //*type 6:  < 
{                                 //*type 7:  >> 
    char    **command;            //*type 8:  << 
    char    *path;                //*type 9:  |  
    t_token *t1;                  //*type 10: $  
    t_exec  *next;
};

#endif