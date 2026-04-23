/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable_relative.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/23 10:42:25 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 10:42:46 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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