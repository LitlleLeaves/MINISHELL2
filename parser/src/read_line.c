/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:53:13 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/22 15:27:10 by jjhurry          ###   ########.fr       */
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

char *safe_readline(void)
{
    char *line;

	// if (!isatty(STDIN_FILENO)) //debug
	// {
	// 	fprintf(stderr, "NON-INTERACTIVE MODE\n");
	// 	// ...
	// }
	// else
    // 	fprintf(stderr, "INTERACTIVE MODE\n");

    if (!isatty(STDIN_FILENO))
    {
        line = get_next_line(STDIN_FILENO); // reads from pipe directly
        if (line)
        {
            // remove trailing newline that gnl includes
            int len = ft_strlen(line);
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
