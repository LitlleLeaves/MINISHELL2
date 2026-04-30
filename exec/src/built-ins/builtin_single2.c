/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:28:07 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/30 12:00:51 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_single_env(char **arguments, t_data *data)
{
	int	i;

	if (arguments[1] != NULL)
	{
		write(2, "wrong amount of argments for env\n", 34);
		data->exit_code = 1;
	}
	else
	{
		i = 0;
		while (data->envp[i] != NULL)
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
	}
}

int	ft_builtin_single_pwd(t_data *data)
{
	char	*buff;
	char	*pwd;

	pwd = ft_getenv(data, "PWD");
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		return (1);
	}
	else
	{
		buff = getcwd(NULL, 0);
		if (buff == NULL)
			return (-1);
		printf("%s\n", buff);
		free(buff);
		return (1);
	}
}
