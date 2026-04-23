/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/03 13:22:09 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 11:40:48 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void ft_unset_helper(t_data *data, int j)
{
		free(data->envp[j]);
		j++;
		while (data->envp[j] != NULL)
		{
			data->envp[j - 1] = data->envp[j];
			j++;
		}
		data->envp[j - 1] = NULL;
}

void ft_unset(char **args, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (data->envp[j] != NULL)
		{
			if (ft_strncmp(args[i], data->envp[j], ft_strlen(args[i] )) == 0 && \
(data->envp[j][ft_strlen(args[i])] == '=' || \
data->envp[j][ft_strlen(args[i])] == '\0'))
			{
				ft_unset_helper(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
}
