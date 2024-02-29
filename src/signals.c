/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:35:58 by mcatalan          #+#    #+#             */
/*   Updated: 2024/02/29 11:34:05 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_signal(t_shell *shell)
{
	if (g_signal)
		shell->end_type = g_signal;
}

static void	prompt_s(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		g_signal = 1;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGTERM)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit (g_signal);
	}
	//segfault if SIGTERM -> ft_isspace
}

static void	here_doc_s(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		printf("ctrl + c\n");
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
		exit(1);
	}
	//segfault if SIGTERM -> here_doc -> ft_strcmp
}

static void	execution_s(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	printf("execution sig: %d\n", sig);
	if (sig == SIGINT)
	{
		g_signal = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
	else if (sig == SIGQUIT)
	{
		printf("ctrl + \\n");
		g_signal = 131;
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
	else if (sig == SIGTERM)
	{
		printf("ctrl + D\n");
		g_signal = 0;
	}
}

void	wait_signal(int type)
{
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	g_signal = 0;
	if (type == PROMPT)
	{
		sig.sa_sigaction = prompt_s;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else if (type == HERE_DOC)
	{
		sig.sa_sigaction = here_doc_s;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else if (type == EXECUTION)
	{
		printf("entra execution\n");
		sig.sa_sigaction = execution_s;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
}
