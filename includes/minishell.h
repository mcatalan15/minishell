/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/01/23 13:09:26 by mcatalan         ###   ########.fr       */
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

// shell_program.c
void	shell_program(t_shell *shell);

// utils.c
void	ft_print_tokens(t_token *tokens);
int		ft_isspace(char c);
int		ft_isoperate(int flag);
int		ft_issquote(char c);
int		ft_isdquote(char c);

// utils2.c
char	*get_cwd(void);
void	exit_program(t_shell *shell, int type);

// errors.c
void	stx_erro(t_shell *shell, int type, char c);

// split_parsing.c
char	**ft_split_shell(char const *str);

#endif