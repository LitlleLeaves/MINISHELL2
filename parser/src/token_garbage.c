/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:17:09 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/16 19:13:31 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_input(t_data *d, char *str)
{
	t_token *head;
	t_token	*current;
	int		start;

	current = NULL;
	d->index = 0;
	while (str[d->index] != '\0')
	{
		start = d->index;
		//make the token
		if (current == NULL)
		{
			current = classify_and_make(d, str + start);
			head = current;
		}
		else
		{
			current->next = classify_and_make(d, str + start);
			current = current->next;
		}
		//printf("%d\n", d->index);
		//printf("%s\n", d->line);
		//d->index = index_to_next_delimeter(str, d->index);
	}
	return (head);
}

t_token	*classify_and_make(t_data *d, char *line)
{
	int		index;

	index = 0;
	while (line[index] == ' ')
		index++;
	if (check_delimeters(line[index]) == 0) //command
		return (if_word(d, index, line));
	else if (line[index] == '|') //pipe
		return (d->index += index + 1 ,make_new_token(ft_strdup("|"), PIPE));
 	else if (line[index] == '>' && line[index + 1] == '>') //append
		return (if_redirection(d, index, line, REDIR_OUT_APP));
 	else if (line[index] == '<' && line[index + 1] == '<') // heredeoc
		return (if_redirection(d, index, line, HEREDOC_EXPANSION));
 	else if (line[index] == '>') // truncate
		return (if_redirection(d, index, line, REDIR_OUT_TRUNC));
 	else if (line[index] == '<') // input
		return (if_redirection(d, index, line, REDIR_IN));
	d->index += index;
	return (NULL);
}

char	*get_line(void)
{
	char	*line;

	line = readline("you are a cog>");
	if (line[0] == '\0')
		return (free(line), NULL);
	if (line == NULL)
	{
		rl_clear_history();
		//sluit ales wat geinitialiseerd is
		exit(0);
	}
	return (line);
}
