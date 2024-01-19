/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/19 20:13:47 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// System .h files
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

// Our .h files
# include "libft/libft.h"
// # include "includes/readline/readline.h"
# include "structs.h"
# include "definitions.h"


// Our .c functions by file
// init_vars.c
int		init_vars(char *line, t_shell *shell);

// utils.c
void	ft_print_tokens(t_token *tokens);

// split_parsing.c
char	**ft_split_shell(char const *str);

#endif