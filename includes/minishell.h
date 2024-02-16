/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/16 12:16:00 by mcatalan         ###   ########.fr       */
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
// main.c

// init_vars.c
int		init_vars(char *line, t_shell *shell);
t_token	*put_tokens(t_token *token, char *str, t_shell *shell);
t_token	*token_new(char *str, int type, t_shell *shell);
int		get_type(char *str);

// shell_program.c
int		shell_program(t_shell *shell);

// errors.c
int		stx_erro(t_shell *shell, char c);
void	nsf_or_dir(t_shell *shell, int type, char *str);
void	rdir_erro(t_shell *shell, int type, char *str);
void	perm_den(t_shell *shell, char *cmd);
void	cmd_nf(t_shell *shell, char *cmd);
void	nsf_or_dir2(t_shell *shell, char *str);

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
void	exec_cmd(t_shell *shell, t_token *aux, int pid);
char	**get_cmd(t_token *token);

// redirections.c
void	redirection(t_shell *shell, t_token *token);
// void	redirect(t_shell *shell, t_token *token);
// t_token	*redirect(t_token *token);


//utils
//clear_free_functions.c
int		clear_list(t_token *token);
int		clear_program(t_shell *shell, int type, int flag);
void	free_dp(char **str, char *s1);
void	free_prompt(t_shell *shell);

//print_functions.c
void	ft_print_tokens(t_token *tokens);
void	ft_print_cmd(char **command);

//quotes.c
int		ft_quoted_closed(char *str);
int		remove_quotes(char *str, char f);
void	kill_all_quotes(char *str);

//get_functions.c
char	*get_cwd(void);
char	*get_expansion(char *sub, char *exp);
int		get_type(char *str);
int		*get_pid(t_token *token);
// utils3.c
char	*addstr(char *str, char c);
t_token	*token_new(char *str, int type, t_shell *shell);
void	join_subt2(t_token *token, char **str, t_token **new,
			t_shell *shell);

// utils4.c
int		cmdlen(t_token *aux);
char	*search_path(t_shell *shell, char **split);

// utils5.c
int		ft_isbuiltin(char *cmd);
void	wait_for_children(t_shell *shell, int *pid);

// ft_is_functions.c
int		ft_isoperate(int flag);
int		ft_issquote(char c);
int		ft_isdquote(char c);
int		ft_isrd(int flag);
char	*ft_is_interrogant(char *end_type);

//built-ins
//echo.c
void	my_echo(t_shell *shell);

//env.c
void	my_env(t_shell *shell);

//exit.c
void	my_exit(t_shell *shell);

//export.c
void	my_export(t_shell *shell);

//pwd.c
void	my_pwd(t_shell *shell);

//unset.c
void	my_unset(t_shell *shell);

//cd.c
void	my_cd(t_shell *shell);

//build-utils.c
void	manage_builtins(t_shell *shell, int built_type);

#endif