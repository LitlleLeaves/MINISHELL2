/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:14:47 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/20 15:56:31 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//parent process waits for all children to finish, and returns the exit status of the last one
static int ft_wait_all_children(t_data *data, int nmb_of_pipes)
{
    int   i;
    int   status;
    pid_t last_pid;
    int   last_status = 0;

    last_pid = data->pids[nmb_of_pipes];

    i = 0;
    while (i < nmb_of_pipes + 1)
    {
        pid_t pid = waitpid(data->pids[i], &status, 0);
        // if (pid == -1)
        // {
        //     
        // }
        if (pid == last_pid)
            last_status = status;
        i++;
    }
    if (WIFEXITED(last_status))
		data->exit_code = WEXITSTATUS(last_status);
	// fprintf(stderr, "exitcode is: %i\n", data->exit_code);
	return (data->exit_code);
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^
//small check for the exitcode so that we know wether the child exited because of the signal or due to something else
//if the signal is the reason we should call an exit func 

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
			ft_setup_pipes(data, nmb_of_pipes, i);
			if (ft_child_process(head, data, i) < 0)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		else
			i++;
	}
	return (1);
}

void ft_no_word_redirection(t_token *head,t_data *data)
{
	t_token	*curr;
	int		in;
	int		out;

	(void)data; //tijdelijk want word nog niet gebruikt hier
	curr = head;
	in = -2;
	out = -2;
	while (curr != NULL)
	{
		if (curr->type == REDIR_IN)
			if (ft_handle_in(&in, curr) < 0)
				return ;
		curr = curr->next;
	}
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

//parent process sets up pipes and pids,check for single builtin and executes it or then forks the children, and waits for them to finish
int ft_start_exec(t_token *head, t_data *data)
{
	int	nmb_of_pipes;

	nmb_of_pipes = ft_find_pipes(head);
	if (nmb_of_pipes == 0 && ft_count_single_words(head) == 0)
	{
		ft_no_word_redirection(head);
		ft_free_tokens(head);
		return (1);
	}
	if (nmb_of_pipes == 0 && ft_check_builtins_before_fork(head, data) > 0)
	{
		ft_free_tokens(head);
		return (1);
	}
	if (ft_create_pipes_and_pids(nmb_of_pipes,data) < 0)
		return (ft_free_tokens(head),-2);
	if (ft_fork_process(head, data, nmb_of_pipes) < 0)
		return (ft_free_tokens(head), ft_close_all_pipes(data, nmb_of_pipes),- 3);
	ft_close_all_pipes(data, nmb_of_pipes);
	// ft_close_heredoc_fds(head);
	ft_wait_all_children(data, nmb_of_pipes);
	ft_cleanup(head, data, nmb_of_pipes);
	return (1);
}

int ft_copy_envp(t_data *data, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
		i++;
	data->envp = ft_calloc(i + 1, sizeof(char *));
	if (data->envp == NULL)
		return (-1);
	j = 0;
	while (j < i)
	{
		data->envp[j] = ft_strdup(envp[j]);
		j++;
	}
	return (1);
}
