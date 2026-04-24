/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:53:09 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 12:40:57 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <errno.h>

// //handle execution failure, free arguments and exit with status 127
// void	ft_execution_failure(char *executable, char **arguments)
// {
// 	ft_free_arr((void **)arguments);
// 	free(executable);
// 	exit(127);
// }
/*find path in envp and build the argument list, 
then find executable path and execute*/
void	ft_child_execute(t_exec_info *exec_info, t_data *data)
{
	char	*executable;

	if (exec_info->fd_in >= 0)
	{
		dup2(exec_info->fd_in, STDIN_FILENO);
		close(exec_info->fd_in);
	}
	if (exec_info->fd_out >= 0)
	{
		dup2(exec_info->fd_out, STDOUT_FILENO);
		close(exec_info->fd_out);
	}
	ft_check_builtins(exec_info, data, exec_info->arguments);
	executable = ft_decide_executable(exec_info->arguments[0], data);
	if (executable == NULL)
	{
		exit(127);
	}
	else
		execve(executable, exec_info->arguments, data->envp);
	write(2, "execution failure\n", 19);
	exit(128);
}

int	ft_build_arguments_array(t_exec_info *exec_info)
{
	int		i;
	t_token	*curr;

	i = 0;
	exec_info->arguments = ft_calloc(exec_info->words + 1, sizeof(char *));
	if (exec_info->arguments == NULL)
		return (-1);
	curr = exec_info->start;
	while (curr != exec_info->end && curr != NULL)
	{
		if (curr->type == WORD)
		{
			exec_info->arguments[i] = ft_strdup(curr->value);
			if (exec_info->arguments[i] == NULL)
			{
				return (ft_free_r((void **)exec_info->arguments, i), -1);
			}
			i++;
		}
		curr = curr->next;
	}
	return (1);
}

//start execution of the command
int	ft_child_start_execute(t_exec_info *exec_info, t_data *data, int i)
{
	t_token	*curr;

	exec_info->fd_in = -2;
	exec_info->fd_out = -2;
	exec_info->command_number = i;
	curr = exec_info->start;
	ft_build_arguments_array(exec_info);
	while (curr != exec_info->end && curr != NULL)
	{
		if (ft_apply_redirection(&exec_info->fd_in, \
&exec_info->fd_out, curr) < 0)
			return (ft_free_arr((void **)exec_info->arguments), -1);
		curr = curr->next;
	}
	if (exec_info->arguments != NULL)
	{
		ft_child_execute(exec_info, data);
	}
	return (1);
}

//find start and end of command
int	ft_find_start_end(int i, t_exec_info *exec_info, t_token *head)
{
	int		counter;
	t_token	*start;
	t_token	*end;

	counter = 0;
	start = head;
	exec_info->words = 0;
	while (counter < i && (start != NULL))
	{
		if (start->type == PIPE)
			counter++;
		start = start->next;
	}
	if (start == NULL || start->type == PIPE)
		return (-1);
	end = start;
	while ((end != NULL) && end->type != PIPE)
	{
		if (end->type == WORD)
			exec_info->words += 1;
		end = end->next;
	}
	exec_info->start = start;
	exec_info->end = end;
	return (1);
}

/*child process finds the start and end of its command,
applies redirections, and executes the command*/
int	ft_child_process(t_token *head, t_data *data, int i)
{
	t_exec_info	exec_info;

	if (ft_find_start_end(i, &exec_info, head) < 0)
		return (-1);
	if (ft_child_start_execute(&exec_info, data, i) < 0)
		return (-3);
	return (1);
}
