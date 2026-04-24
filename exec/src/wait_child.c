/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:52:17 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 12:54:22 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_last_exitstatus(t_data *data, int last_status)
{
	if (WIFEXITED(last_status))
		data->exit_code = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
	{
		data->exit_code = 128 + WTERMSIG(last_status);
		if (WTERMSIG(last_status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(last_status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
}

/*parent process waits for all children to finish, 
and returns the exit status of the last one*/
int	ft_wait_all_children(t_data *data, int nmb_of_pipes)
{
	int		i;
	int		status;
	pid_t	last_pid;
	int		last_status;
	pid_t	pid;
	
	last_status = 0;
	last_pid = data->pids[nmb_of_pipes];
	i = 0;
	while (i < nmb_of_pipes + 1)
	{
		pid = waitpid(data->pids[i++], &status, 0);
		if (pid == last_pid)
			last_status = status;
	}
	ft_last_exitstatus(data, last_status);
	return (data->exit_code);
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^
//small check for the exitcode so that we know wether the child exited because 
//of the signal or due to something else
//if the signal is the reason we should call an exit func 