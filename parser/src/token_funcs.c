/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:36:59 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/29 14:39:11 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_new_token(char *value, t_token_type type)
{
	t_token	*token;
	char	*temp;

	token = malloc(sizeof(t_token) * 1);
	if (!token)
		return (printf("malloc error"), NULL);
	if (!value)
		temp = NULL;
	else
	{
		temp = value;
		if (!temp)
			return (printf("value error"), NULL);
	}
	token->value = temp;
	token->type = type;
	token->next = NULL;
	token->filename = NULL;
	return (token);
}

t_token	*if_word(t_data *d, int start, char *line)
{
	t_token	*token;
	int		i;
	char	*value;

	i = 0;
	if (line[start] == '\'' || line[start] == '"')
	{
		if (line[start + 1] != line[start])
			return (if_quotes(d, line, start));
		else
			return (make_word_token_with_quotes(d, line, start));
	}
	while (check_delimeters(line[i + start]) == 0 && line[i + start] != '\0' \
&& (line[i + start] != '\'' && line[i + start] != '"'))
		i++;
	if ((line[i + start] == '\'' || line[i + start] == '"') && \
line[i + start] == line[i + start + 1])
		return (make_word_token_with_quotes(d, line, start));
value = ft_substr(line, start, i);
	if (!value)
		return (printf("substr error"), NULL);
	token = make_new_token(value, WORD);
	d->index += i + start;
	return (token);
}

int	index_to_char(char	*str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && str[index] != c)
		index++;
	return (index);
}

char	*get_file_name(char *line, int *index)
{
	char	*value;
	int		start;

	start = 0;
	if (line[start] == '\'' || line[start] == '"')
	{
		(*index) = index_to_char(line + start + 1, line[start]);
		start++;
	}
	else
	{
		while (check_delimeters(line[(*index)]) == 0 && line[(*index)] != '\0')
			(*index)++;
	}
	value = ft_substr(line, start, (*index));
	if (!value)
		return (NULL);
	if (line[(*index)] != '\0' \
&& (line[(*index + 1)] == '\'' || line[(*index + 1)] == '"'))
		(*index) += 2;
	return (value);
}

t_token	*if_redirection(t_data *d, int start, char *line, t_token_type type)
{
	int		index;
	char	*value;
	t_token	*token;

	index = 0;
	while (check_delimeters(line[start]) == 1 \
&& (line[start] != '\'' && line[start] != '"'))
	{
		start++;
		if (line[start] == '\0')
		{
			d->index += index + start;
			return (NULL);
		}
	}
	if ((line[start] == '\'' || line[start] == '"') && type == HEREDOC)
	{
		type = HEREDOC_NO_EXPANSION;
	}
	value = get_file_name(line + start, &index);
	if (!value)
		return (NULL);
	token = make_new_token(value, type);
	d->index += index + start;
	return (token);
}
