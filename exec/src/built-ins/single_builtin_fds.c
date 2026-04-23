/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_builtin_fds.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/23 10:35:48 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 10:36:29 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//apply redirection if applicable
int ft_single_redirection(t_token *curr, int *fd_in, int *fd_out, t_data *data)
{
	while (curr != NULL)
	{
		if (ft_apply_redirection(fd_in, fd_out, curr) < 0)
		{
			data->exit_code = 1;
			return (-1);
		}
		curr = curr->next;	
	}
	return (1);
}

void	ft_builtin_fds(t_single_fds fds, int words, char **arguments, t_data *data)
{
	if (fds.fd_in >= 0)
    {
		fds.std_in = dup(STDIN_FILENO);
        dup2(fds.fd_in, STDIN_FILENO);
        close(fds.fd_in);
    }
    if (fds.fd_out >= 0)
    {
        fds.std_out = dup(STDOUT_FILENO);
        dup2(fds.fd_out, STDOUT_FILENO);
        close(fds.fd_out);
    }
    ft_execute_single_builtin(words, arguments, data);
    if (fds.std_in >= 0)
    {
        dup2(fds.std_in, STDIN_FILENO);
        close(fds.std_in);
    }
    if (fds.std_out >= 0)
    {
        dup2(fds.std_out, STDOUT_FILENO);
        close(fds.std_out);
    }
}