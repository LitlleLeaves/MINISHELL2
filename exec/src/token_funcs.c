// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   token_funcs.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/18 20:36:59 by side-lan          #+#    #+#             */
// /*   Updated: 2026/04/16 15:09:14 by jjhurry          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "exec.h"
// #include "parser.h"

// t_token	*make_new_token(char *value, t_token_type type)
// {
// 	t_token	*token;
// 	char	*temp;

// 	token = malloc(sizeof(t_token) * 1);
// 	if (!token)
// 		return (printf("malloc error"), NULL);
// 	if (!value)
// 		temp = NULL;
// 	else
// 	{
// 		temp = strdup(value);
// 		if (!temp)
// 			return (printf("value error"), NULL);
// 	}
// 	token->value = temp;
// 	token->type = type;
// 	token->next = NULL;
// 	//printf("token:%s\n", token->value);
// 	return (token);	
// }

// int		check_delimeters(char c)
// {
// 	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\0')
// 		return (1);
// 	return (0);
// }

// t_token	*if_quotes(t_data *d, char *line, int start)
// {
// 	char	c_to_find;
// 	int		index;
// 	char	*value;

// 	index = 0;
// 	c_to_find = line[start];
// 	if (line[start] != '\0')	
// 		start++;
// 	while (line[start + index] != '\0' && line[start + index] != c_to_find)
// 		index++;
// 	if (index == 0)
// 	{
// 		value = ft_strdup("");
// 		d->index += start + 2;
// 		return (make_new_token(value, WORD));
// 	}
// 	value = ft_substr(line, start, index);
// 	d->index += index + start + 1;
// 	return (make_new_token(value, WORD));
// }

// t_token	*if_word(t_data *d, int start, char *line)
// {	
// 	t_token	*token;
// 	int		index;
// 	char	*value;

// 	index = 0;
// 	if (line[start] == '\'' || line[start] == '"')
// 	{
// 		return (if_quotes(d, line, start));
// 	}
// 	while (check_delimeters(line[index + start]) == 0 && line[index + start] != '\0' \
// 			&& (line[index + start] != '\'' && line[index + start] != '"'))
// 		index++;
// 	value = ft_substr(line, start, index);
// 	if (!value)
// 		return (printf("substr error"), NULL);
// 	token = make_new_token(value, WORD);
// 	free(value);
// 	d->index += index + start;
// 	return (token);
// }

// int	index_to_char(char	*str, char c)
// {
// 	int	index;
	
// 	index = 0;
// 	while (str[index] != '\0' && str[index] != c)
// 		index++;
// 	return (index);
// }

// t_token *if_redirection(t_data *d, int start, char *line, t_token_type type)
// {
// 	int		index;
// 	char 	*value;
// 	t_token	*token;

// 	index = 0;
// 	while (check_delimeters(line[start]) == 1)
// 	{
// 		start++;
// 		if (line[start] == '\0')
// 			return (d->index += start + 1, make_new_token(ft_strdup(""), type));
// 	}
// 	if (line[start] == '\'' || line[start] == '"')
// 		index = index_to_char(line + start + 1, line[start]);
// 	else
// 	{
// 		while (check_delimeters(line[start + index]) == 0 && line[index + start] != '\0')
// 			index++;
// 	}
// 	value = ft_substr(line, start, index);	
// 	if (!value)
// 		return (NULL);
// 	token = make_new_token(value, type);
// 	d->index += index + start;
// 	return (token);
// }

// t_token *if_heredoc(t_data *d, int start, char *line, t_token_type type)
// {
// 	int		index;
// 	char 	*value;
// 	t_token	*token;

// 	index = 0;
// 	while (check_delimeters(line[start]) == 1)
// 	{
// 		start++;
// 		if (line[start] == '\0')
// 			return (d->index += start + 1, make_new_token(ft_strdup(""), type));
// 	}
// 	if (line[start] == '\'' || line[start] == '"')
// 		index = index_to_char(line + start + 1, line[start]);
// 	else
// 	{
// 		while (check_delimeters(line[start + index]) == 0 && line[index + start] != '\0')
// 			index++;
// 	}
// 	value = ft_substr(line, start, index);	
// 	if (!value)
// 		return (NULL);
// 	token = make_new_token(value, type);
// 	d->index += index + start;
// 	return (token);
// }
