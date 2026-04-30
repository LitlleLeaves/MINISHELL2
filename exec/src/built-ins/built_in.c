/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:29:13 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/30 12:00:37 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_cd(t_exec_info *exec_info, t_data *data, char **arguments)
{
	if (exec_info->words > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		ft_child_builtin_cleanup(data, arguments);
		exit (1);
	}
	else if (exec_info->words == 1)
		data->exit_code = ft_cd_no_arguments(data);
	else if (exec_info->words == 2)
		data->exit_code = ft_cd_one_argument(arguments, data);
	ft_child_builtin_cleanup(data, arguments);
	exit (data->exit_code);
}

void	ft_builtin_export(t_data *data, char **arguments)
{
	if (arguments[1] == NULL)
		ft_export_print_list(data);
	else
		ft_add_to_export_list(arguments, data);
	ft_child_builtin_cleanup(data, arguments);
	exit (data->exit_code);
}

void	ft_builtin_unset(t_data *data, char **arguments)
{
	if (arguments[1] != NULL)
		ft_unset(arguments, data);
	ft_child_builtin_cleanup(data, arguments);
	exit (0);
}

void	ft_builtin_echo(t_data *data, char **arguments)
{
	if (arguments[1] == NULL)
		data->exit_code = ft_echo_no_arguments();
	else if (ft_check_echo_option(arguments) == 2)
		data->exit_code = ft_echo_no_newline(arguments, 2);
	else
		data->exit_code = ft_echo_newline(arguments, 1);
	ft_child_builtin_cleanup(data, arguments);
	exit(data->exit_code);
}

void	ft_builtin_exit(t_exec_info *exec_info, t_data *data, char **arguments)
{
	data->shutdown = 1;
	if (exec_info->words == 1)
	{
		data->exit_code = data->exit_code;
	}
	else if (exec_info->words == 3)
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
	ft_child_builtin_cleanup(data, arguments);
	exit (data->exit_code);
}
