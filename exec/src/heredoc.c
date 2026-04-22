/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:53:13 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/22 16:35:17 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdint.h>
#include <stdio.h>


int ft_heredoc_create_file(t_token *curr, t_data *data)
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
	if (file  == NULL)
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

char *ft_heredoc_replace_line(char *line, char *key, char *value, int start)
{
	int		key_len;
	int		value_len;
	char	*new_line;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	new_line = ft_calloc((ft_strlen(line) - key_len - 1) + value_len + 1, sizeof(char));
	if (new_line == NULL)
		return (NULL);
	if (start != 0)
		ft_memcpy(new_line, line, start);
	ft_memcpy(new_line + start, value, value_len);
	ft_memcpy(new_line + value_len + start, line + start + key_len + 1, \
ft_strlen(line) - start - key_len - 1);
	free(line);
	return (new_line);
}

char *ft_heredoc_expansion_helper(int key_len, char *line, int i, t_data *data)
{
	char	*key;
	char	*value;
	
	key = ft_substr(line, i , key_len);
		if (key == NULL )
			return (NULL);
	value = ft_getenv(data, key);
		if (value == NULL)
			value = "";
	line = ft_heredoc_replace_line(line, key, value, i - 1);
	free(key);
	return (line);
}

char *ft_heredoc_expansion(char *line, t_data *data)
{
	int		i;
	int		key_len;

	i = 0;
	while (line[i] != '\0')
	{
		key_len = 0;
		if (line[i] == '$')
		{
			i++;
			if (line[i] != '_' && !ft_isalpha(line[i]))
				continue;
			while(ft_isalnum(line[i + key_len]) == 1 || line[i + key_len] == '_')
				key_len++;	
			line = ft_heredoc_expansion_helper(key_len, line, i, data);
			if (line == NULL)
				return (NULL);
			i = i - 1;
		}
		if (line[i] != '$')
			i++;
	}
	return (line);
}

int ft_heredoc_parsing(t_token *curr, t_data *data)
{
    char *line;

	line = NULL;
    if (ft_heredoc_create_file(curr, data) < 0)
        return (-1);
    setup_signals(HEREDOC);
	rl_event_hook = heredoc_signal_hook;
	while (1)
    {
        line = readline("> ");
        if (signal_received)
        {
			signal_received = 0;
			setup_signals(INTERACTIVE);
			close(curr->heredoc_fd);
			data->sig = HEREDOC_INT;
			rl_event_hook = NULL;
			free(line);
			return (-2);
        }
        if (!line)
            break;
        if (ft_strncmp(line, curr->value, ft_strlen(curr->value)) == 0)
        {
            free(line);
            break;
        }
        if (curr->type == HEREDOC_EXPANSION && ft_strchr(line, '$'))
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
		data->line = NULL;
		line = NULL;
    }
    setup_signals(INTERACTIVE);
	rl_event_hook = NULL;
    close(curr->heredoc_fd);
    return (1);
}

int handle_heredoc(t_token *head, t_data *data)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (curr->type == HEREDOC_EXPANSION || curr->type == HEREDOC_NO_EXPANSION)
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
