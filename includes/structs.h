/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:18:52 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/08 12:12:26 by jpaul-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token		t_token;
typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct s_flag		t_flag;
// typedef struct s_vars
// {
//     char **path;
//     char **env;
// }t_vars;

struct	s_token
{
	char		*str;
	int			type;
	t_shell		*shell;
	t_token		*next;
	t_token		*prev;
};

struct	s_command
{
	char	**cmd;
	char	*path;
	int		fd[2];
	int		pid;
	t_token	*token;
};

struct s_shell
{
	char		**env;
	int			end_type;
	t_command	*command;
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