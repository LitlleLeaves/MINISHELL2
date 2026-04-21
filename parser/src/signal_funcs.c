/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:06:58 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/21 15:26:44 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle the signal while a heredoc is open
void	heredoc_handler(int signum)
{
    (void)signum;
	extern int	rl_done;

    // write(STDOUT_FILENO, "\nMinishell>", 11);
    write(STDOUT_FILENO, "\n", 2);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_done = 1;
	signal_received = 1;
}

//handle signal during the interactive state
void interactive_handler(int signum)
{
    (void)signum;

    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	signal_received = 1;
}

//func to call whenever we transition between different states ie; child, interactive heredoc and ignore
void	setup_signals(t_sig_status	type)
{
	struct sigaction sa;

	if (type == NON_INTERACTIVE)//na t leze van de eerte lijn maar wet nog niet wat anders is dan n kind
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (type == CHILD) // roep aan in het begin van de kind process
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (type == HEREDOC || type == INTERACTIVE) // roep aan in het begin (interactive) of wann we heredocs opstarte
	{
		if (type == HEREDOC)
			sa.sa_handler = heredoc_handler;
		if (type == INTERACTIVE)
			sa.sa_handler = interactive_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (type == IGNORE) //roep aan voor dat we n kind make
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
