/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:30:48 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/22 20:52:26 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

// static char	*stringify_enum(t_token_type token);
//static void	print_tokenized_list(t_data	*data);
static void	ft_init_data(t_data *data);

//global exit status is nodig voor signals
volatile sig_atomic_t signal_received = 0;

static void	ft_init_data(t_data *data)
{
	data->current = NULL;
	data->head = NULL;
	data->line = NULL;
	data->shutdown = -1;
	data->exit_code = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 1)
		return (10);
	argv[0] = 0;
	ft_init_data(&data);
	if (ft_copy_envp(&data, envp) == -1)
		return (printf("errorenvp"));
	main_loop(&data);
	ft_free_arr((void **)data.envp);
	rl_clear_history();
	return (0);
}

int	get_input(t_data *data)
{
	add_history(data->line);
	check_expansions(data);
	if (data->line == NULL)
		return (-1);
	data->head = tokenize_input(data, data->line);
	data->current = data->head;
	//print_tokenized_list(data);
	free(data->line);
	data->line = NULL;
	return (0);
}

//main loop of te shell
int		main_loop(t_data *data)
{
	data->line = NULL;
	data->head = NULL;
	data->sig = NOTHING;
	while (1)
	{
		free(data->line);
		ft_free_tokens(data->head, data);
		signal_received = 0;
		setup_signals(INTERACTIVE);
		data->line = get_line(data);
		if (check_closed_quotes(data->line))
		{
			printf("Error: unclosed quotes\n");
			continue ;
		}
		if (data->sig == INTERACTIVE_INT)
			continue ;
		if (data->sig == INTERACTIVE_KILL)
			exit(0);
		if (data->line && *data->line)
		{
			if (get_input(data) == -1)
				continue ;
		}
		if (data->head == NULL)
			continue ;
		if (execute_input(data) == -1)
			continue ;
		if (data->shutdown != -1)
		{
			ft_free_tokens(data->head, data);
			ft_free_arr((void **)data->envp);
			rl_clear_history();
			exit(data->exit_code);
		}
	}
	return (0);
}

int	execute_input(t_data *data)
{
	if (data->head == NULL)
		return (0);
	if (handle_heredoc(data->head, data) < 0)
		return (ft_free_arr((void **)data->envp), ft_free_tokens(data->head, data), -1);
	if (ft_start_exec(data->head, data) < 0)
		return (ft_free_arr((void **)data->envp), ft_free_tokens(data->head, data), -1);
	return (0);
}
