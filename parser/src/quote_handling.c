/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:36:30 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/30 14:43:32 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*make_word_with_quote_helper(t_data *d, int len, char *value, \
char *line)
{
	if (line[d->index + len] == '\0')
	{
		d->index += len;
		return (make_new_token(value, WORD));
	}
	else
		d->index += len + 1;
	return (make_new_token(value, WORD));
}

static int	update_quote_count(int check)
{
	if (check == 1)
		return (0);
	else
		return (1);
}

int	check_closed_quotes(char *line)
{
	int	index;
	int	single_check;
	int	double_check;

	index = 0;
	double_check = 0;
	single_check = 0;
	while (line[index])
	{
		if (line[index] == '\'')
			single_check = update_quote_count(single_check);
		if (line[index] == '"')
			double_check = update_quote_count(double_check);
		index++;
	}
	if (double_check == 1 || single_check == 1)
		return (-1);
	return (0);
}

t_token	*make_word_token_with_quotes(t_data *d, char *line)
{
	char	*value;
	int		read;
	int		write;
	int		len;

	read = 0;
	write = 0;
	len = 0;
	while (line[len] && check_delimeters(line[len]) == 0)
		len++;
	value = ft_substr(line, 0, len);
	if (!value)
		return (NULL);
	while (value[read])
	{
		if (value[read] != '\'' && value[read] != '"')
		{
			value[write] = value[read];
			write++;
		}
		read++;
	}
	value[write] = '\0';
	return (make_word_with_quote_helper(d, read, value, line));
}

t_token	*if_quotes(t_data *d, char *line, int start)
{
	char	c_to_find;
	int		index;
	char	*value;

	index = 0;
	c_to_find = line[start];
	if (line[start] != '\0')
		start++;
	while (line[start + index] != '\0' && line[start + index] != c_to_find)
		index++;
	if (index == 0)
	{
		value = ft_strdup("");
		d->index += start + 1;
		return (make_new_token(value, WORD));
	}
	value = ft_substr(line, start, index);
	d->index += index + start + 1;
	return (make_new_token(value, WORD));
}
