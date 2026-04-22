/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:56:47 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/22 15:42:08 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "exec.h"

void ft_relative_executable_help(char *command)
{
	if (access(command, X_OK) == -1)
	{
		if (errno == EACCES)
		{
			write(2, "Minishell: ", 12);
			write(2, command, ft_strlen(command));
			write(2, ": Permission denied\n", 21);
			exit(126);
		}
		else
		{
			perror(command);
			exit(126);
		}
	}
}

//check whether the relative path exsists and if the file is executable
char *ft_relative_executable(char *command)
{
	struct stat	st;

	if (stat(command, &st) == -1)
	{
		if (errno == ENOENT)
		{
			write(2, "Minishell: ", 12);
			write(2, command, ft_strlen(command));
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
		else
		{
			perror(command);
			exit(126);
		}
	}
	if (S_ISDIR(st.st_mode))
	{
		write(2, "Minishell: ", 12);
		write(2, command, ft_strlen(command));
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
	
	return (ft_relative_executable_help(command), strdup(command));
}

//make a executable by looking through the path and finding if it is executable
char *ft_make_executable(char *executable, t_data *data)
{
	int		i;
	char	**paths;
	char	*exec;
	char	*path;

	if (executable[0] == '\0')
		return ("");
	paths = ft_split(ft_getenv(data, "PATH"), ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (path == NULL)
			return (ft_free_arr((void **)paths), NULL);
		exec = ft_strjoin(path, executable);
		if (exec == NULL)
			return (ft_free_arr((void **)paths), free(path), NULL);
		if (access(exec, F_OK) == 0)
			return (free(path), ft_free_arr((void **)paths), exec);
		i++;
		free(path);
		free(exec);
	}
	ft_free_tokens(data->head, data);
	access(exec, F_OK);
	write(2, executable, ft_strlen(executable));
	write(2,": ", 3);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 2);

	return (ft_free_arr((void **)paths), NULL);
}

//decide if the exucatble path is relative or if it needs to be found in the path, and return the executable path
char *ft_decide_executable(char *command, t_data *data)
{
	char	*executable;

	if (ft_strchr(command, '/') == NULL)
		executable = ft_make_executable(command, data);
	else
		executable = ft_relative_executable(command);
	return (executable);
}

//choose executable is a built in or regular executable, and execute it
void ft_check_builtins(t_exec_info *exec_info, t_data *data, char **arguments)
{
	if (ft_strncmp(arguments[0], "cd", 2) == 0)
		ft_builtin_cd(exec_info, data, arguments);
	else if (ft_strncmp(arguments[0], "export", 6) == 0)
		ft_builtin_export(data, arguments);
	else if (ft_strncmp(arguments[0], "unset", 5) == 0)
		ft_builtin_unset(data, arguments);
	else if (ft_strncmp(arguments[0], "echo", 4) == 0)
		ft_builtin_echo(data, arguments);
	else if (ft_strncmp(arguments[0], "exit", 4) == 0)
		ft_builtin_exit(exec_info ,data, arguments);
	else if (ft_strncmp(arguments[0], "env", 3) == 0)
		ft_builtin_env(data, arguments);
	else if (ft_strncmp(arguments[0], "pwd", 3) == 0)
		ft_builtin_pwd(data, arguments);
}
