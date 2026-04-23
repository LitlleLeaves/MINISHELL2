/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_builtin_execution.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/18 13:07:12 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 10:35:32 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//count the words
int ft_count_single_words(t_token *head)
{
	t_token	*curr;
	int		words;

	curr = head;
	words = 0;
	while (curr != NULL)
	{
		if (curr->type == WORD)
			words++;
		curr = curr->next;
	}
	return (words);
}

//check to handle builtin or not
int ft_check_single_builtin(char **arguments)
{
	if (ft_strncmp(arguments[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(arguments[0], "echo", 4) == 0)
		return (2);
	else if (ft_strncmp(arguments[0], "pwd", 3) == 0)
		return (3);
	else if (ft_strncmp(arguments[0], "export", 6) == 0)
		return (4);
	else if (ft_strncmp(arguments[0], "unset", 5) == 0)
		return (5);
	else if (ft_strncmp(arguments[0], "env", 3) == 0)
		return (6);
	else if (ft_strncmp(arguments[0], "exit", 4) == 0)
		return (7);
	else
		return (0);
}

//actual builtin execution
int ft_execute_single_builtin(int words, char **arguments, t_data *data)
{
	if (ft_strncmp(arguments[0], "cd", 2) == 0)
		return(ft_builtin_single_cd(words, arguments, data), 1);
	else if (ft_strncmp(arguments[0], "echo", 4) == 0)
		return(ft_builtin_single_echo(arguments, data), 2);
	else if (ft_strncmp(arguments[0], "pwd", 3) == 0)
		return(ft_builtin_single_pwd(data), 3);
	else if (ft_strncmp(arguments[0], "export", 6) == 0)
		return(ft_builtin_single_export(arguments, data), 4);
	else if (ft_strncmp(arguments[0], "unset", 5) == 0)
		return(ft_builtin_single_unset(arguments, data), 5);
	else if (ft_strncmp(arguments[0], "env", 3) == 0)
		return(ft_builtin_single_env(arguments, data), 6);
	else if (ft_strncmp(arguments[0], "exit", 4) == 0)
		return(ft_builtin_single_exit(words, arguments, data), 7);
	return (0);
}

//built list of size words
int ft_single_argument_list(t_token *curr, int words, char **arguments)
{
	int	counter;

	counter = 0;
	while (counter < words && curr != NULL)
	{
		if (curr->type == WORD)
		{
			arguments[counter] = ft_strdup(curr->value);
			if (arguments[counter] == NULL)
				return (ft_free_r((void **)arguments, counter), -1);
			counter++;
		}
		curr = curr->next;
	}
	return (1);
}

//main single builtin chekc, first checks if its a builtin command, then applies redirecion and executes the code
int ft_check_builtins_before_fork(t_token *head, t_data *data)
{
	t_token			*curr;
	int				words;
	char			**arguments;
	t_single_fds	fds;

	curr = head;
	words = ft_count_single_words(curr);
	fds.fd_in = -2;
	fds.fd_out = -2;
	fds.std_in = -1;
	fds.std_out = -1;

	arguments = ft_calloc(words + 1, sizeof(char *));
	if (arguments == NULL)
		return (-1);
	ft_single_argument_list(curr , words, arguments);
	if (ft_check_single_builtin(arguments) == 0)
		return (ft_free_arr((void **)arguments),-1);
	if (ft_single_redirection(curr, &fds.fd_in, &fds.fd_out, data) < 0)
		return(ft_free_arr((void **)arguments), 2);
	ft_builtin_fds(fds, words, arguments, data);
    ft_free_arr((void **)arguments);
    return (1);
}
