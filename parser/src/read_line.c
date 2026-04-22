/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:53:13 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/21 17:55:02 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//roept getline en checked de return waarde
char	*get_line(t_data *data)
{
	char	*line;

	line = safe_readline();
	if (signal_received == 1)
    {
	    data->exit_code = 130;
        if (line)
            free(line);
		signal_received = 0;
		rl_done = 0;
        return (NULL);
    }
	else if (line == NULL)
	{
		rl_clear_history();
		//sluit ales wat geinitialiseerd is;
		ft_free_arr((void **)data->envp);
		exit(0);
	}
	if (line[0] == '\0' && signal_received == 0)
		return (free(line), NULL);
	return (line);
}

char	*safe_readline(void)
{
	char	*line;

	rl_event_hook = interactive_signal_hook;
	rl_done = 0;
	line = readline("Minishell>");
	rl_event_hook = NULL;
	return (line);
}
