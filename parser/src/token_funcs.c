/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:36:59 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/22 20:46:28 by side-lan         ###   ########.fr       */
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
	//printf("token:%s\n", token->value);
	return (token);	
}

// int		check_delimeters(char c)
// {
// 	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\0')
// 		return (1);
// 	return (0);
// }

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

t_token	*make_word_token_with_quotes(t_data *d, char *line, int start)
{
	int		index;
	char	*value;
	int		length;
	int		quote_index;

	quote_index = 0;
	index = 0;
	length = 0;
	while (line[index] != '\0' && check_delimeters(line[index]) == 0)
	{
		if (line[index] != '\'' || line[index] != '"')
			length++;
		index++;
	}
	value = ft_substr(line, start, index);
	start += index;
	index = 0;
	while (value[quote_index + index] != '\0')
	{
		if (value[quote_index + index] == '\'' || value[quote_index + index] == '"')
		{
			value[quote_index + index] = value[quote_index + index + 1];
			value[quote_index + index + 1] = value[quote_index + index + 2];
			value[quote_index + index + 2] = value[quote_index + index + 3];
			quote_index += 3;
			printf("yewehere\n");
		}
		else
			value[quote_index + index] = value[quote_index + index];
		index++;
	}
	printf("%s\n", value);
	d->index += index + start + 1;
	return (make_new_token(value, WORD));
}


//char	*cut_empty_string_from_string(char *line, int start)
//{
//	int	index;
	
//	index = 0;
//	while ()
	
//}

t_token	*if_word(t_data *d, int start, char *line)
{	
	t_token	*token;
	int		index;
	char	*value;

	index = 0;
	if (line[start] == '\'' || line[start] == '"')
	{
		if (line[start + 1] != line[start])
			return (if_quotes(d, line, start));
		else
			return (make_word_token_with_quotes(d, line, start));
	}
	while (check_delimeters(line[index + start]) == 0 && line[index + start] != '\0' \
			&& (line[index + start] != '\'' && line[index + start] != '"'))
		index++;
	value = ft_substr(line, start, index);
	if (!value)
		return (printf("substr error"), NULL);
	token = make_new_token(value, WORD);
	// free(value);
	d->index += index + start;
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
	if (line[(*index)] != '\0' && (line[(*index + 1)] == '\'' || line[(*index + 1)] == '"'))
		(*index) += 2;
	return (value);
}

t_token *if_redirection(t_data *d, int start, char *line, t_token_type type)
{
	int		index;
	char 	*value;
	t_token	*token;

	index = 0;
	while (check_delimeters(line[start]) == 1 && (line[start] != '\'' && line[start] != '"'))
	{
		start++;
		if (line[start] == '\0')
		{
			d->index += index + start;
			return (NULL);
		}
	}
	if ((line[start] == '\'' || line[start] == '"') && type == HEREDOC_EXPANSION)
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

