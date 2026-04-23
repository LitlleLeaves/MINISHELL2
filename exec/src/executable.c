/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/12 14:56:47 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 11:38:20 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "exec.h"

char	*ft_exec_failure(t_data *data, char *executable, char **paths)
{
	ft_free_tokens(data->head, data);
	write(2, executable, ft_strlen(executable));
	write(2, ": command not found\n", 20);
	ft_free_arr((void **)paths);
	exit(127);
}

/*make a executable by looking through 
the path and finding if it is executable*/
char	*ft_make_executable(char *executable, t_data *data)
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
		path = ft_strjoin(paths[i++], "/");
		if (path == NULL)
			return (ft_free_arr((void **)paths), NULL);
		exec = ft_strjoin(path, executable);
		if (exec == NULL)
			return (ft_free_arr((void **)paths), free(path), NULL);
		if (access(exec, F_OK) == 0)
			return (free(path), ft_free_arr((void **)paths), exec);
		free(path);
		free(exec);
	}
	return (ft_exec_failure(data, executable, paths), NULL);
}

/*decide if the exucatble path is relative or if it needs 
to be found in the path, and return the executable path*/
char	*ft_decide_executable(char *command, t_data *data)
{
	char	*executable;

	if (ft_strchr(command, '/') == NULL)
		executable = ft_make_executable(command, data);
	else
		executable = ft_relative_executable(command);
	return (executable);
}

//choose executable is a built in or regular executable, and execute it
void	ft_check_builtins(t_exec_info *exec_info, t_data *data, char **args)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_builtin_cd(exec_info, data, args);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_builtin_export(data, args);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_builtin_unset(data, args);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_builtin_echo(data, args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ft_builtin_exit(exec_info, data, args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_builtin_env(data, args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_builtin_pwd(data, args);
}
