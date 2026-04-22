/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:23:46 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/22 20:53:07 by side-lan         ###   ########.fr       */
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
		while (d->line[index] == '$' && d->line[index + 1] != ' ')
		{
				convert_expansions(d, index);
		}
		index++;
	}
}

//bool	remove_quotes_from_empty_key(t_data *d, int start)
//{
	//char	*new;
	//int		total_len;
//
	//total_len = ft_strlen(d->line);
	//new = malloc(ft_strlen(d->line) - 1);
	//ft_strlcpy(new, d->line, start);
	//new[start] = '$';
	//ft_strlcat(new, d->line + start + 1, total_len);
	//free(d->line);
	//d->line = new;
	//return (true);
//}

char	*get_key(char *line, int start)
{
	int		index;
	char	*key;

	index = 1;
//	if ((line[start + index] == '\'' && line[start - 1] == '\'')\
//|| (line[start + index] == '"' && line[start - 1] == '"') )
		//return (printf("jatoch\n"), NULL);
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
		check = replace_key_in_line(d, value, start, 1);
		return (free(value), check);
	}
	key = get_key(d->line, start);
	key_length = ft_strlen(key);
	value = ft_getenv(d, key);
	free(key);
	if (!value)
	{
		if (replace_key_in_line(d, " ", start, key_length) == false)
			d->line = NULL;
		return (false);
	}
	length = ft_strlen(value);
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
	total_len = (val_len - key_len) - 1 + old_length;
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
