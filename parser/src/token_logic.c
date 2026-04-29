/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:17:09 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/29 16:28:29 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	index_over_char(char *str, char c);

//loop door de string en maak de linked list van tokens
t_token	*tokenize_input(t_data *d, char *str)
{
	t_token	*head;
	t_token	*current;

	current = NULL;
	d->index = 0;
	head = NULL;
	head = tokenize_loop(d, str, head, current);
	if (!head)
		return (NULL);
	return (head);
}

t_token	*tokenize_loop(t_data *d, char *str, t_token *head, t_token *current)
{
	int	start;

	while (str[d->index] != '\0')
	{
		start = d->index;
		start = index_over_char(str, ' ');
		if (str[start] == '\0')
			return (head);
		d->index = start;
		if (current == NULL)
		{
			current = classify_and_make(d, str + start);
			if (current == NULL)
				return (NULL);
			head = current;
		}
		else
		{
			current->next = classify_and_make(d, str + start);
			if (current->next == NULL)
				return (ft_free_tokens(head, d), NULL);
			current = current->next;
		}
	}
	return (head);
}

static int	index_over_char(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && str[index] == c)
		index++;
	return (index);
}
//bepaald met de delimeters welke token we maken
t_token	*classify_and_make(t_data *d, char *line)
{
	int		index;

	index = 0;
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
