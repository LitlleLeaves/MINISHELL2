/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:31:15 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/29 17:12:54 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_export_valid_char(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_export_validity_checker(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '=')
		return (0);
	if (ft_isdigit(str[0]) == 1 || str[0] == '\0')
		return (0);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_export_valid_char(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

//helper function
static int	ft_key_value_helper(char *argument, t_data *data)
{
	char	*key;
	char	*value;
	int		j;
	int		res;

	j = 0;
	while (argument[j] != '=')
		j++;
	key = ft_calloc(j + 1, sizeof(char));
	value = ft_strdup(argument + j + 1);
	if (key == NULL || value == NULL)
		return (-1);
	ft_strlcpy(key, argument, j + 1);
	res = ft_change_env_key_value(key, value, data);
	free(key);
	free(value);
	return (res);
}

void	ft_not_valid_checker(int i, char **arguments, t_data *data)
{
	write(2, "Minishell: export: `", 20);
	write(2, arguments[i], strlen(arguments[i]));
	write(2, "': not a valid identifier\n", 26);
	data->exit_code = 1;
	i++;
}

//add either a key or key and value pair to env
int	ft_add_to_export_list(char **arguments, t_data *data)
{
	int		i;
	char	*entry;

	i = 1;
	while (arguments[i] != NULL)
	{
		if (ft_export_validity_checker(arguments[i]) == 0)
		{
			ft_not_valid_checker(i, arguments, data);
			i++;
			continue ;
		}
		if (ft_strchr(arguments[i], '=') == NULL)
		{
			entry = ft_strdup(arguments[i]);
			if (entry == NULL)
				return (data->shutdown = 1, -1);
			ft_change_env_key(entry, data);
		}
		else
			if (ft_key_value_helper(arguments[i], data) < 0)
				return (data->shutdown = 1, -1);
		i++;
	}
	return (1);
}
