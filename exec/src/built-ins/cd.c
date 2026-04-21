/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:27:13 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/21 17:07:34 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <errno.h>

//helper funtion that sets the env variable OLDPWD and PWD to the actual new values
int ft_set_pwd_oldpwd(t_data *data)
{
	int		i;
	char	*old_pwd;
	char 	*curr_pwd;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if ((ft_strncmp(data->envp[i], "PWD", 3) == 0 && data->envp[i][3] == '='))
		{
			old_pwd = ft_strdup(ft_getenv(data, "PWD"));
			curr_pwd = getcwd(NULL, 0);
			if (old_pwd == NULL || curr_pwd == NULL)
				return (-1);
			if (ft_change_env_key_value("OLDPWD", old_pwd, data) < 0)
				return (-2);
			ft_change_env_key_value("PWD", curr_pwd, data);
			free(old_pwd);
			free(curr_pwd);
			return (2);
		}
		i++;
	}
	return (1);
}

//cd with no argument to home
int ft_cd_no_arguments(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME");
	if (home == NULL)
	{
		write(2, "Minishell: cd: HOME not set\n", 29);
		return (1);
	}
	if (chdir(home) == -1)
	{
		write(2, "Minishell: ", 12);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		return (1);
	}
	else	
		ft_set_pwd_oldpwd(data);
	return (0);
}

//cd helper funtion
void ft_cd_helper(t_token **curr)
{
	int	count;

	count = 0;
	while (*curr != NULL)
	{
		if ((*curr)->type == WORD)
			count++;
		if (count == 2)
			break;
		*curr = (*curr)->next;
	}
}

void ft_print_cd_error(char *path)
{
	write(2, "Minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": ", 3);
	write(2, strerror(errno),ft_strlen(strerror(errno)));
	write(2, "\n", 2);
}

//cd funciton that checks ~ variable at start of a path
int ft_cd_one_argument(char **arguments, t_data *data)
{
	char	*path;
	char	*home;

	path = NULL;
	if (ft_strncmp(arguments[1], "~", 1) == 0)
	{
		home = ft_getenv(data, "HOME");
		if (arguments[1][1] != '\0')
			path = ft_strjoin(home, arguments[1] + 1);
		else
			path = ft_strdup(home);
		if (path  == NULL)
			return (data->shutdown = 1 ,1);
		if (chdir(path) == -1)
			return (ft_print_cd_error(path), free(path), 1);
	}
	else 
		if (chdir(arguments[1]) == -1)
			return (ft_print_cd_error(arguments[1]), 1);
	ft_set_pwd_oldpwd(data);
	return (free(path), 0);
}
