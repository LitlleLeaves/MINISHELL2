/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:29:24 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/08 16:33:16 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void ft_builtin_env(t_data *data, char **arguments)
{
	int	i;

	if (arguments[1] != NULL)
	{
		write(2, "wrong amount of arguments for env\n", 34);
		data->exit_code = 1	;
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
	ft_child_builtin_cleanup(data, arguments);
	exit(data->exit_code);
}

void ft_builtin_pwd(t_data *data, char **arguments)
{
	char	*buff;
	char	*pwd;
	
	pwd = ft_getenv(data, "PWD");
    if (pwd != NULL)
    {
        printf("%s\n", pwd);
    }
	else
	{
		buff = getcwd(NULL, 0);
		if (buff == NULL)
			return (free(arguments), exit(1));
		printf("%s\n", buff);
		free(buff);
	}
	ft_child_builtin_cleanup(data, arguments);
	exit(0);
}
