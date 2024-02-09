/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/09 13:07:38 by mcatalan         ###   ########.fr       */
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
int		shell_program(t_shell *shell, char *str);

// utils.c
void	ft_print_tokens(t_token *tokens);
int		ft_isoperate(int flag);
int		ft_issquote(char c);
int		ft_isdquote(char c);
void	join_subt2(t_token *token, char **str, t_token **new,
			t_shell *shell);

// utils2.c
char	*get_cwd(void);
int		clear_program(t_shell *shell, int type, int flag);
int		ft_quoted_closed(char *str);
char	*get_expansion(char *sub, char *exp);
int		clear_list(t_token *token);

// utils3.c
char	*ft_is_interrogant(char *end_type);
int		remove_quotes(char *str, char f);
char	*addstr(char *str, char c);
t_token	*token_new(char *str, int type, t_shell *shell);
int		get_type(char *str);

// utils4.c
void	kill_all_quotes(char *str);
int		cmdlen(t_token *aux);
void	ft_print_cmd(char **command);
char	*search_path(t_shell *shell, char **split);

// utils5.c
int		ft_isbuiltin(char *cmd);

// errors.c
int		stx_erro(t_shell *shell, char c);
void	rdir_erro(t_shell *shell, int type);
void	perm_den(t_shell *shell, char *cmd);
void	cmd_nf(t_shell *shell, char *cmd);

// expansion.c
t_token	*expanding(t_token *token, char **env);
void	add_new_token(t_token **new, char **str, t_shell *shell);
int		expand(t_token *token, char **env, char *str, int pos);
t_token	*split_expansion(t_token *token, char flag, int *p, char **env);

// expansion2.c
int		skipped(char *str);
char	*skipped2(char **env, char *str, char *tmp);
int		get_type2(char flag, int *p, int *len);
t_token	*get_token(t_token *token, char **env);
t_token	*add_subtokens(t_token *token, t_token *aux, t_token *next, char **env);

// split_parsing.c
char	**ft_split_shell(char const *str);

// execute.c
void	exec_cmd(t_shell *shell, t_token *aux);
char	**get_cmd(t_token *token);

// redirections.c
// void	redirect(t_shell *shell, t_token *token);
// t_token	*redirect(t_token *token);

#endif