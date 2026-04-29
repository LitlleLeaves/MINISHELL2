/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:06:58 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/29 11:47:10 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int signum)
{
	(void)signum;
	g_signal_received = 1;
}

void	interactive_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal_received = 1;
}

int	heredoc_signal_hook(void)
{
	if (g_signal_received == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
	}
	return (0);
}

//handle signal during the interactive state
int	interactive_signal_hook(void)
{
	if (g_signal_received == 1)
	{
		rl_done = 1;
	}
	return (0);
}

//func to call whenever we transition between different states
void	setup_signals(t_sig_status	type)
{
	struct sigaction	sa;

	if (type == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (type == HEREDOC_SIG || type == INTERACTIVE)
	{
		if (type == HEREDOC_SIG)
			sa.sa_handler = heredoc_handler;
		if (type == INTERACTIVE)
			sa.sa_handler = interactive_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (type == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
