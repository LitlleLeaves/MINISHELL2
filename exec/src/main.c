/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:14:47 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 12:52:56 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//fork a proces for each command
int	ft_fork_process(t_token *head, t_data *data, int nmb_of_pipes)
{
	int	i;

	i = 0;
	data->nmb_of_pipes = nmb_of_pipes;
	while (i < nmb_of_pipes + 1)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (-1);
		else if (data->pids[i] == 0)
		{
			setup_signals(CHILD);
			ft_setup_pipes(data, nmb_of_pipes, i);
			if (ft_child_process(head, data, i) < 0)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		else
			i++;
		setup_signals(IGNORE);
	}
	return (1);
}

void	ft_no_word_redir_help(t_token *curr, int *in)
{
	while (curr != NULL)
	{
		if (curr->type == REDIR_IN)
			if (ft_handle_in(in, curr) < 0)
				return ;
		curr = curr->next;
	}
}

void	ft_no_word_redirection(t_token *head)
{
	t_token	*curr;
	int		in;
	int		out;

	curr = head;
	in = -2;
	out = -2;
	ft_no_word_redir_help(curr, &in);
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == REDIR_OUT_APP)
			ft_handle_out_app(&out, curr);
		if (curr->type == REDIR_OUT_TRUNC)
			ft_handle_out_trunc(&out, curr);
		curr = curr->next;
	}
	if (in > -1)
		close(in);
	if (out > -1)
		close(out);
}
/*parent process sets up pipes and pids,
check for single builtin and executes it
or then forks the children, and waits for them to finish*/
int ft_start_exec(t_token *head, t_data *data)
{
	int	nmb_of_pipes;

	nmb_of_pipes = ft_find_pipes(head);
	if (nmb_of_pipes == 0 && ft_count_single_words(head) == 0)
	{
		ft_no_word_redirection(head);
		ft_free_tokens(head, data);
		return (1);
	}
	if (nmb_of_pipes == 0 && ft_check_builtins_before_fork(head, data) > 0)
	{
		ft_free_tokens(head, data);
		return (1);
	}
	if (ft_create_pipes_and_pids(nmb_of_pipes, data) < 0)
		return (ft_free_tokens(head, data), -2);
	if (ft_fork_process(head, data, nmb_of_pipes) < 0)
		return (ft_free_tokens(head, data), \
ft_close_all_pipes(data, nmb_of_pipes), -3);
	ft_close_all_pipes(data, nmb_of_pipes);
	ft_wait_all_children(data, nmb_of_pipes);
	ft_cleanup(head, data, nmb_of_pipes);
	return (1);
}
