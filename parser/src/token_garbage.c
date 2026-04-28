/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:17:09 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/28 19:58:31 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//loop door de string en maak de linked list van tokens
t_token	*tokenize_input(t_data *d, char *str)
{
	t_token	*head;
	t_token	*current;
	int		start;

	current = NULL;
	d->index = 0;
	while (str[d->index] != '\0')
	{
		start = d->index;
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
	}
	return (head);
}

//bepaald met de delimeters welke token we maken
t_token	*classify_and_make(t_data *d, char *line)
{
	int		index;

	index = 0;
	while (line[index] == ' ')
		index++;
	if (check_delimeters(line[index]) == 0)
		return (if_word(d, index, line));
	else if (line[index] == '|')
		return (d->index += index + 1, make_new_token(ft_strdup("|"), PIPE));
	else if (line[index] == '>' && line[index + 1] == '>')
		return (if_redirection(d, index, line, REDIR_OUT_APP));
	else if (line[index] == '<' && line[index + 1] == '<')
		return (if_redirection(d, index, line, HEREDOC));
	else if (line[index] == '>')
		return (if_redirection(d, index, line, REDIR_OUT_TRUNC));
	else if (line[index] == '<')
		return (if_redirection(d, index, line, REDIR_IN));
	d->index += index;
	return (NULL);
}
