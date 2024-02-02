/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul-kr <jpaul-kr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/02 10:54:02 by jpaul-kr         ###   ########.fr       */
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

// Readline .h files
# include "readline/readline.h"
# include "readline/history.h"

// Our .h files
# include "libft/libft.h"
# include "structs.h"
# include "definitions.h"

// Our .c functions by file
// init_vars.c
int		init_vars(char *line, t_shell *shell);
t_token	*put_tokens(t_token *token, char *str, t_shell *shell);
t_token	*token_new(char *str, int type, t_shell *shell);
int		get_type(char *str);

// shell_program.c
int		shell_program(t_shell *shell);

// utils.c
void	ft_print_tokens(t_token *tokens);
int		ft_isspace(char c);
int		ft_isoperate(int flag);
int		ft_issquote(char c);
int		ft_isdquote(char c);

// utils2.c
char	*get_cwd(void);
int		clear_program(t_shell *shell, int type, int flag);
int		ft_quoted_closed(char *str);
char	*get_expansion(char *sub, char *exp);
int		clear_list(t_token *token);

// utils3.c
char	*ft_is_interrogant(char *end_type, int *len);
void	remove_quotes(char *str, char f);

// errors.c
int		stx_erro(t_shell *shell, char c);

// expansion.c
t_token	*expanding(t_token *token, char **env);

// split_parsing.c
char	**ft_split_shell(char const *str);

#endif