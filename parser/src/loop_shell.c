/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:30:48 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/20 17:55:27 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*stringify_enum(t_token_type token);
//static void	print_tokenized_list(t_data	*data);
static void	ft_init_data(t_data *data);

//global exit status is nodig voor signals
volatile sig_atomic_t exit_status = 0;

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

//main loop of te shell
int		main_loop(t_data *data)
{
	while (1)
	{
		setup_signals(INTERACTIVE);
		data->line = get_line(data);
		setup_signals(NON_INTERACTIVE);
		if (data->line && *data->line)
		{
			if (get_input(data) == -1)
				continue ;
		}
		if (data->head == NULL)
			continue ;
		if (execute_input(data) == -1)
			return (-1);
		if (data->shutdown != -1)
		{
			ft_free_arr((void **)data->envp);
			rl_clear_history();
			exit(data->exit_code);
		}
	}
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
	return (0);
}

int	execute_input(t_data *data)
{
	if (handle_heredoc(data->head, data) < 0)
		return (ft_free_arr((void **)data->envp), ft_free_tokens(data->head), -1);
	if (ft_start_exec(data->head, data) < 0)
		return (ft_free_arr((void **)data->envp), ft_free_tokens(data->head), -1);
	return (0);
}

//roept getline en checked de return waarde
char	*get_line(t_data *data)
{
	char	*line;

	line = readline("Minishell>");
	if (exit_status == 130)
    {
	    exit_status = 0;
        if (line)
            free(line);
        return (NULL);
    }
	if (line == NULL)
	{
		rl_clear_history();
		//sluit ales wat geinitialiseerd is;
		ft_free_arr((void **)data->envp);
		exit(0);
	}
	if (line[0] == '\0' && exit_status != 130)
		return (free(line), NULL);
	return (line);
}

//static void	print_tokenized_list(t_data	*data)
//{
//	while (data->current != NULL)
//	{
//		if (data->current->value == NULL)
//			data->current = data->current->next;
//		// printf("%s %s\n", data->current->value, stringify_enum(data->current->type));
//		data->current = data->current->next;
//	}
//}

// static char	*stringify_enum(t_token_type token)
// {
// 	if (token == WORD)
// 		return ("WORD");
// 	if (token == PIPE)
// 		return ("PIPE");
// 	if (token == REDIR_OUT_APP)
// 		return ("REDIR_OUT_APP");
// 	if (token == REDIR_OUT_TRUNC)
// 		return ("REDIR_OUT_TRUNC");
// 	if (token == REDIR_IN)
// 		return ("REDIR_IN");
// 	if (token == HEREDOC_EXPANSION)
// 		return ("HEREDOC_EXPANSION");
// 	if (token == HEREDOC_NO_EXPANSION)
// 		return ("HEREDOC_NO_EXPANSION");
// 	return (NULL);
// }
