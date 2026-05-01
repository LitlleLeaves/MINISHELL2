/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:23:46 by side-lan          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:03 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	convert_expansion_helper(t_data *d, int start, \
int key_length, char *value);

void	check_expansions(t_data *d)
{
	int				index;
	char			find;

	find = 0;
	index = 0;
	while (d->line[index] != '\0')
	{
		if (d->line[index] == '\'')
		{
			find = d->line[index];
			index++;
			while (d->line[index] != find)
				index++;
		}
		else if (d->line[index + 1] == '"' && d->line[index] == '$')
			index++;
		else
		{
			while (d->line[index] == '$' && d->line[index + 1] != ' ' && \
d->line[index + 1] != '\0')
				convert_expansions(d, index);
		}
		index++;
	}
}

char	*get_key(char *line, int start)
{
	int		index;
	char	*key;

	index = 1;
	if (line[start] == '\'' || line[start] == '"')
		return (NULL);
	while (line[start + index] != '\0' && \
check_delimeters(line[start + index]) == 0 && \
line[start + index] != '"' && line[start + index] != '\'')
		index++;
	key = ft_substr(line, start, index);
	if (!key)
		return (printf("error in getkey\n"), NULL);
	return (key);
}

bool	convert_expansions(t_data *d, int start)
{
	char	*key;
	char	*value;
	int		key_length;
	bool	check;

	start++;
	if (d->line[start] == '?')
	{
		value = ft_itoa(d->exit_code);
		check = replace_key_in_line(d, value, start, 1);
		return (free(value), check);
	}
	key = get_key(d->line, start);
	if (!key)
	{
		if (replace_key_in_line(d, NULL, start, 0) == false)
			d->line = NULL;
		return (false);
	}
	key_length = ft_strlen(key);
	value = ft_getenv(d, key);
	free(key);
	return (convert_expansion_helper(d, start, key_length, value));
}

static bool	convert_expansion_helper(t_data *d, int start, \
int key_length, char *value)
{
	if (!value)
	{
		if (replace_key_in_line(d, "", start, key_length) == false)
			d->line = NULL;
		return (false);
	}
	if (replace_key_in_line(d, value, start, key_length) == false)
		return (printf("ERROR\n"), false);
	return (true);
}

bool	replace_key_in_line(t_data *d, char *value, int start, int key_len)
{
	char	*new;
	int		val_len;
	int		old_length;
	int		total_len;

	old_length = ft_strlen(d->line);
	val_len = ft_strlen(value);
	total_len = (val_len - key_len) + old_length + 4;
	new = malloc(total_len + 1);
	if (!new)
		return (false);
	ft_strlcpy(new, d->line, start);
	if (value)
		ft_strlcat(new, value, val_len + start);
	ft_strlcat(new, d->line + start + key_len, total_len);
	free(d->line);
	d->line = new;
	return (true);
}
