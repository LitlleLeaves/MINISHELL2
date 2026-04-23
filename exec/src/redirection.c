/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/12 12:04:50 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 11:01:19 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <errno.h>
#include <unistd.h>

//infile regular
int ft_handle_in(int *fd_in, t_token *curr)
{
	if (*fd_in >= 0)
		close(*fd_in);
	*fd_in = open(curr->value, O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		write(2, "Minishell: ", 12);
		write(2, curr->value, ft_strlen(curr->value));
		write(2, ": ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 2);
    	return (-1); 
	}
	return (*fd_in);
}

//infile heredoc
int ft_handle_in_heredoc(int *fd_in, t_token *curr)
{
	if (*fd_in >= 0)
		close(*fd_in);
	*fd_in = open(curr->filename, O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		write(2, "Minishell: ", 12);
		write(2, curr->value, ft_strlen(curr->value));
		write(2, ": ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 2);
    	return (-1); 
	}
	return (*fd_in);
}

//outfile append
int ft_handle_out_app(int *fd_out, t_token *curr)
{
	if (*fd_out >= 0)
		close(*fd_out);
	*fd_out = open(curr->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*fd_out == -1)
	{
		write(2, "Minishell: ", 12);
		write(2, curr->value, ft_strlen(curr->value));
		write(2, ": ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 2);
    	return (-1);
	}
	return (*fd_out);
}

//outfile trucation
int ft_handle_out_trunc(int *fd_out, t_token *curr)
{
		if (*fd_out >= 0)
		close(*fd_out);
	*fd_out = open(curr->value, O_WRONLY| O_TRUNC | O_CREAT, 0644);
	if (*fd_out == -1)
	{
		write(2, "Minishell: ", 12);
		write(2, curr->value, ft_strlen(curr->value));
		write(2, ": ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 2);
    	return (-1);
	}
	return (*fd_out);
}

//handle redirection and save command
int ft_apply_redirection(int *fd_in, int *fd_out, t_token *curr)
{
	if (curr->type == REDIR_IN)
        return (ft_handle_in(fd_in, curr));
    else if (curr->type == HEREDOC_EXPANSION || curr->type == HEREDOC_NO_EXPANSION)
        return (ft_handle_in_heredoc(fd_in, curr));
    else if (curr->type == REDIR_OUT_APPEND)
        return (ft_handle_out_app(fd_out, curr));
    else if (curr->type == REDIR_OUT_TRUNCT)
        return (ft_handle_out_trunc(fd_out, curr));
    return (1);
}
