/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:57:45 by jpaul-kr          #+#    #+#             */
/*   Updated: 2024/01/22 11:12:25 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

// Colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define SPACE ' '
# define TAB '\t'
# define PIPE '|'

// exit codes
# define EXIT_SUCCESS 0
# define PATH_ERROR 127
# define NO_PERM 126

// # define SIG_INT
// 128 + SIG_INT
# define FALSE -1
# define TRUE 1
# define FAILURE -1
# define SUCCESS 1

// token values
# define T_NULL 0
# define T_STR 1
# define T_REDIN 2
# define T_REDOUT 3
# define T_DIN 4
# define T_DOUT 5
# define T_DOLLAR 6
# define T_PIPE 7
# define T_SQUOTE 8
# define T_DQUOTE 9

#endif