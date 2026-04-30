/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:53:13 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/30 12:39:19 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//roept getline en checked de return waarde
char	*get_line(t_data *data)
{
	char	*line;

	line = safe_readline();
	if (g_signal_received == 1)
	{
		data->exit_code = 130;
		if (line)
			free(line);
		g_signal_received = 0;
		rl_done = 0;
		return (NULL);
	}
	else if (line == NULL)
	{
		rl_clear_history();
		ft_free_arr((void **)data->envp);
		exit(0);
	}
	if (line[0] == '\0' && g_signal_received == 0)
		return (free(line), NULL);
	return (line);
}

char	*safe_readline(void)
{
	char	*line;
	int		len;

	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
		}
		return (line);
	}
	else
	{
		rl_event_hook = interactive_signal_hook;
		rl_done = 0;
		line = readline("Minishell>");
		rl_event_hook = NULL;
		return (line);
	}
}

int	get_input(t_data *data)
{
	add_history(data->line);
	if (check_closed_quotes(data->line))
		return (printf("Error: unclosed quotes\n"), -1);
	check_expansions(data);
	if (data->line == NULL)
		return (-1);
	data->head = tokenize_input(data, data->line);
	data->current = data->head;
	free(data->line);
	data->line = NULL;
	return (0);
}
