/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:36:30 by side-lan          #+#    #+#             */
/*   Updated: 2026/05/01 13:39:34 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*make_word_with_quote_helper(t_data *d, int len, char *value, \
char *line)
{
	if (line[len] == '\0')
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

int	ft_make_word_quote_helper(char *value)
{
	int	read;
	int	write;
	int	quote_char;

	quote_char = 0;
	read = 0;
	write = 0;
	while (value[read])
	{
		if ((value[read] == '\'' || value[read] == '"'))
		{
			if (quote_char == 0)
				quote_char = value[read];
			else if (quote_char == value[read])
				quote_char = 0;
			else
				value[write++] = value[read];
			read++;
		}
		else
			value[write++] = value[read++];
	}
	value[write] = '\0';
	return (read);
}

t_token	*make_word_token_with_quotes(t_data *d, char *line)
{
	char	*value;
	int		read;
	int		len;
	char	qc;

	read = 0;
	qc = 0;
	len = 0;
	while (line[len])
	{
		if ((line[len] == '\'' || line[len] == '"') && qc == 0)
			qc = line[len];
		else if (line[len] == qc)
			qc = 0;
		else if (qc == 0 && check_delimeters(line[len]))
			break ;
		len++;
	}
	value = ft_substr(line, 0, len);
	if (!value)
		return (NULL);
	read = ft_make_word_quote_helper(value);
	return (make_word_with_quote_helper(d, read, value, line));
}
