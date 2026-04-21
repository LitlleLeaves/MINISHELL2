/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:52:21 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/21 17:43:32 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "exec.h"

//free array that is null terminated
void ft_free_arr(void **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// free an array from [0] to [i] incase of malloc failure
void ft_free_r(void **array, int i)
{
	while (i >= 0)
	{
		free(array[i--]);
	}
	free(array);
}

//free the linked list of tokens after execution is done
void ft_free_tokens(t_token *head)
{
	t_token	*curr;
	t_token	*temp;

	curr = head;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->value);
		free(temp->filename);
		free(temp);
	}
	head = NULL;
}

//cleanup function to free all allocated memory at the end of execution, including the linked list of tokens, the array of pids and the array of pipes
void ft_cleanup(t_token *head, t_data *data, int nmb_of_pipes)
{
	int	i;

	ft_free_tokens(head);
	free(data->pids);
	i = 0;
	while (i < nmb_of_pipes)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
}

void ft_child_builtin_cleanup(t_data *data, char **arguments)
{
	ft_free_arr((void **)arguments);
	ft_free_tokens(data->head);
	ft_free_arr((void **)data->envp);
	ft_free_r((void **)data->pipes, data->nmb_of_pipes - 1);
	free(data->pids);
}