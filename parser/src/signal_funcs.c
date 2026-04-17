/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:06:58 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/17 19:51:34 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int signum)
{
	signum = 0;
	//print spc dingetjes goed;'
	//vgm precies hetzelfde als 
	printf("huheredoc?\n");
	exit(130);
}

void	interactive_handler(int signum)
{
	signum = 0;
	//print ^c en promt n nieuwe line
	//opruimfunctie oproepe die 130 terug geeft
	printf("ja heel interactive dit\n");
	exit(130);
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
			sa.sa_handler = *heredoc_handler;
		if (type == INTERACTIVE)
			sa.sa_handler = *interactive_handler;
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
