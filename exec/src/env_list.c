/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:55:38 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/30 11:56:11 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*function that parses the x= part of the env variables
and returns onlue the value part*/
char	*ft_getenv(t_data *data, char *var)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], var, len) == 0 \
&& data->envp[i][len] == '=')
			return (data->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

//create a new list of size+1 and copy and then add the new env variable
int	ft_extend_env(t_data *data, char *entry)
{
	int		i;
	char	**new_list;

	i = 0;
	while (data->envp[i] != NULL)
		i++;
	new_list = ft_calloc(i + 2, sizeof(char *));
	if (new_list == NULL)
		return (-1);
	i = 0;
	while (data->envp[i] != NULL)
	{
		new_list[i] = ft_strdup(data->envp[i]);
		if (new_list[i] == NULL)
			return (ft_free_arr((void **)new_list), -2);
		free(data->envp[i]);
		i++;
	}
	new_list[i] = entry;
	free(data->envp);
	data->envp = new_list;
	return (1);
}

//change a key/value pair if it exists otherwise add to the list
int	ft_change_env_key_value(char *key, char *value, t_data *data)
{
	int		i;
	int		len;
	char	*entry;

	i = 0;
	len = ft_strlen(key) + ft_strlen(value) + 2;
	entry = ft_calloc(len, sizeof(char));
	if (entry == NULL)
		return (-1);
	ft_strlcpy(entry, key, len);
	ft_strlcat(entry, "=", len);
	ft_strlcat(entry, value, len);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0 \
&& data->envp[i][ft_strlen(key)] == '=')
		{
			free(data->envp[i]);
			return (data->envp[i] = entry, 1);
		}
		i++;
	}
	return (ft_extend_env(data, entry));
}

//change a value if already present, otherwise increase the env
int	ft_change_env_key(char *entry, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], entry, ft_strlen(entry)) == 0 \
&& (data->envp[i][ft_strlen(entry)] == '=' \
|| data->envp[i][ft_strlen(entry)] == '\0'))
		{
			free(entry);
			return (1);
		}
		i++;
	}
	if (ft_extend_env(data, entry) < 0)
		return (-2);
	return (2);
}
