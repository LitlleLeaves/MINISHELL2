/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:23:46 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/22 15:50:23 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h" 

void	check_expansions(t_data *d)
{
	int		index;
	// bool	check;

	index = 0;
	while (d->line[index] != '\0')
	{

		if (d->line[index] == '\'')
		{
			index++;
			while (d->line[index] != '\'' && d->line[index] != '\0')
				index++;
		}
		while (d->line[index] == '$' && d->line[index + 1] != ' ' && d->line[index + 1] != '"')
		{
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
	//if (line[start + index] == '\'' || line[start + index] == '"')
		//return (); moete ff kieke of we quotes zien als vlaide keys anders word dit n error
	while (line[start + index] != '\0' && check_delimeters(line[start + index]) == 0 && \
			line[start +index] != '"' && line[start +index] != '\'')
		index++;
	key = ft_substr(line, start, index);
	// fprintf(stderr, "key = %s\n", key);
	if (!key)
		return (printf("error in getkey\n"), NULL);
	return (key);
}

bool	convert_expansions(t_data *d, int start)
{
	char	*key;
	char	*value;
	int		length;
	int		key_length;
	bool	check;

	start++;
	if (d->line[start] == '?')
	{
		value = ft_itoa(d->exit_code);
		check = replace_key_in_line(d, value, start - 1, ft_strlen(value), 1);
		return (free(value), check);
	}
	key = get_key(d->line, start);
	key_length = ft_strlen(key);
	value = ft_getenv(d, key);
	free(key);
	if (!value)
	{
		if (replace_key_in_line(d, " ", start - 1, 1, key_length) == false)
			d->line = NULL;
		return (false);
	}
	length = ft_strlen(value);
	if (replace_key_in_line(d, value, start - 1, length, key_length) == false)
		return (printf("ERROR\n"), false);
	return (true);
}

bool	replace_key_in_line(t_data *d, char *value, int start, int val_len, int key_len)
{
	int		index;
	char	*new;
	int		old_len;
	int		tot_len;
	int		val_index;
	int		len_diff;

	val_index = 0;
	index = 0;
	old_len = ft_strlen(d->line);
	len_diff = (val_len - key_len) - 1;
	if (key_len == old_len && !value)
		return (false);
	tot_len = len_diff + old_len;
	new = ft_calloc(tot_len + 1, sizeof(char));
	if (!new)
		return (printf("mallocerror\n"), false);
	while (index < start)
	{
		new[index] = d->line[index];
		index++;
	}
	while (index < start + val_len)
		new[index++] = value[val_index++];
	while (index < tot_len)
	{
		new[index] = d->line[index - len_diff];
		index++;
	}
	new[index] = '\0';
	// printf("%s\n", new);
	free(d->line);
	d->line = new;
	return (true);
}
