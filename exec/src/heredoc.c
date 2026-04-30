/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:53:13 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/30 12:04:53 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

int	ft_heredoc_create_file(t_token *curr, t_data *data)
{
	static int	counter;
	char		*tmp;
	char		*tmp2;
	char		*file;

	counter++;
	tmp = ft_itoa((int)(uintptr_t)data);
	tmp2 = ft_itoa(counter);
	if (tmp == NULL || tmp2 == NULL)
		return (-1);
	file = ft_strjoin("/tmp/heredoc", tmp);
	free(tmp);
	if (file == NULL)
		return (-2);
	tmp = file;
	file = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	if (file == NULL)
		return (-3);
	curr->heredoc_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	curr->filename = strdup(file);
	if (curr->heredoc_fd == -1)
		return (free(file), -4);
	return (free(file), 1);
}

void	ft_heredoc_sig(t_data *data, t_token *curr, char *line)
{
	g_signal_received = 0;
	data->exit_code = 130;
	setup_signals(INTERACTIVE);
	close(curr->heredoc_fd);
	data->sig = HEREDOC_INT;
	rl_event_hook = NULL;
	free(line);
}

int	ft_heredoc_parsing_loop(char *line, t_data *data, t_token *curr)
{
	while (1)
	{
		line = readline("> ");
		if (g_signal_received)
			return (ft_heredoc_sig(data, curr, line), -2);
		if (!line)
			break ;
		if (ft_strncmp(line, curr->value, ft_strlen(curr->value)) == 0)
		{
			free(line);
			break ;
		}
		if (curr->type == HEREDOC && ft_strchr(line, '$'))
		{
			data->line = line;
			check_expansions(data);
			line = data->line;
			if (!line)
				return (-1);
		}
		write(curr->heredoc_fd, line, ft_strlen(line));
		write(curr->heredoc_fd, "\n", 1);
		free(line);
	}
	return (1);
}

int	ft_heredoc_parsing(t_token *curr, t_data *data)
{
	char	*line;

	line = NULL;
	if (ft_heredoc_create_file(curr, data) < 0)
		return (-1);
	setup_signals(HEREDOC_SIG);
	rl_event_hook = heredoc_signal_hook;
	ft_heredoc_parsing_loop(line, data, curr);
	line = NULL;
	data->line = NULL;
	setup_signals(INTERACTIVE);
	rl_event_hook = NULL;
	close(curr->heredoc_fd);
	return (1);
}

int	handle_heredoc(t_token *head, t_data *data)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (curr->type == HEREDOC \
|| curr->type == HEREDOC_NO_EXPANSION)
		{
			if (ft_heredoc_parsing(curr, data) < 0)
			{
				setup_signals(INTERACTIVE);
				return (-1);
			}
		}
		curr = curr->next;
	}
	return (1);
}
