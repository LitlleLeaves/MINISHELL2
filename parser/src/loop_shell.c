/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:30:48 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/16 19:12:57 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

static char	*stringify_enum(t_token_type token);
static void	print_tokenized_list(t_data	*data);

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		return (10);
	argv[0] = 0;
	main_loop(envp);
	return (0);
}

void	ft_init_data(t_data *data)
{
	data->current = NULL;
	data->head = NULL;
	data->line = NULL;
	data->shutdown = -1;
	data->exit_code = 0;
}

//main loop of te shell
int		main_loop(char	*envp[])
{
	t_data	data;

    //signal(SIGINT, handle_sigint); // voor sigint luistere
	//signal(SIGQUIT, handle_sigquit); // voor sigquit
	ft_init_data(&data);
	if (ft_copy_envp(&data, envp) == -1)
		return (printf("error"));
	while (1)
	{
		data.line = get_line();
		if (data.line && *data.line)
		{
			add_history(data.line);
			check_expansions(&data);
			// check_expansions(&data);
			if (data.line == NULL)
				break ;
			data.head = tokenize_input(&data, data.line);
			data.current = data.head;
			print_tokenized_list(&data);
			free(data.line);
			if (handle_heredoc(data.head, &data) < 0)
				return (ft_free_arr((void **)data.envp), ft_free_tokens(data.head), -1);
			if (ft_start_exec(data.head, &data) < 0)
				return (ft_free_arr((void **)data.envp), ft_free_tokens(data.head), -1);
		}
		if (data.shutdown != -1)
		{
			ft_free_arr((void **)data.envp);
			rl_clear_history();
			exit(data.exit_code);
		}
	}
	ft_free_arr((void **)data.envp);
	rl_clear_history();	
	return (0);
}

static void	print_tokenized_list(t_data	*data)
{
	while (data->current != NULL)
	{
		if (data->current->value == NULL)
			data->current = data->current->next;
		printf("%s %s\n", data->current->value, stringify_enum(data->current->type));
		data->current = data->current->next;
	}
}

static char	*stringify_enum(t_token_type token)
{
	if (token == WORD)
		return ("WORD");
	if (token == PIPE)
		return ("PIPE");
	if (token == REDIR_OUT_APP)
		return ("REDIR_OUT_APP");
	if (token == REDIR_OUT_TRUNC)
		return ("REDIR_OUT_TRUNC");
	if (token == REDIR_IN)
		return ("REDIR_IN");
	if (token == HEREDOC_EXPANSION)
		return ("HEREDOC_EXPANSION");
	if (token == HEREDOC_NO_EXPANSION)
		return ("HEREDOC_NO_EXPANSION");
	return (NULL);
}
