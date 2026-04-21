/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:28:04 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/21 11:58:02 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <errno.h>
#include <limits.h>

void ft_builtin_single_cd(int words, char **arguments, t_data *data)
{
	if (words > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		data->exit_code = 1;
	}
	else if (words == 1)
		data->exit_code = ft_cd_no_arguments(data);
	else if (words == 2)
		data->exit_code = ft_cd_one_argument(arguments, data);
}

void ft_builtin_single_export(char **arguments, t_data *data)
{
	if (arguments[1] == NULL)
		ft_export_print_list(data);
	else
		ft_add_to_export_list(arguments, data);
}

void ft_builtin_single_unset(char **arguments, t_data *data)
{
		if (arguments[1] == NULL)
			return ;
		else
			ft_unset(arguments, data);
}

void ft_builtin_single_echo(char **arguments, t_data *data)
{
	if (arguments[1] == NULL)
		data->exit_code = ft_echo_no_arguments();
	else if (ft_check_echo_option(arguments) == 2)
		data->exit_code = ft_echo_no_newline(arguments, 2);
	else
		data->exit_code = ft_echo_newline(arguments, 1);
}

void ft_builtin_single_exit(int words, char **arguments, t_data *data)
{
	write(2, "exit\n", 5);
	data->shutdown = 1;	
	if (words == 1)
	{
		data->exit_code = 0;
	}
	else if (words == 3)
	{
		write(2, "Minishell: exit: too many arguments\n", 37);
		data->exit_code = 1;
	}
	else
	{
		data->exit_code = ft_exit_code_atol(arguments[1]);
		if (data->exit_code == -1)
		{
			data->exit_code = 2;
			write (2, "Minishell: exit: ", 18);
			write (2, arguments[1], ft_strlen(arguments[1]));
			write (2, ": numeric argument required\n", 29);
		}
	}
}

