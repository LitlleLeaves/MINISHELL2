/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:19:37 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/29 17:20:10 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_build_arguments_array(t_exec_info *exec_info)
{
	int		i;
	t_token	*curr;

	i = 0;
	exec_info->arguments = ft_calloc(exec_info->words + 1, sizeof(char *));
	if (exec_info->arguments == NULL)
		return (-1);
	curr = exec_info->start;
	while (curr != exec_info->end && curr != NULL)
	{
		if (curr->type == WORD)
		{
			exec_info->arguments[i] = ft_strdup(curr->value);
			if (exec_info->arguments[i] == NULL)
			{
				return (ft_free_r((void **)exec_info->arguments, i), -1);
			}
			i++;
		}
		curr = curr->next;
	}
	return (1);
}