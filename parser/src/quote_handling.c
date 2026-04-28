/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:36:30 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/28 19:08:24 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_closed_quotes(char *line)
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
		{
			if (single_check == 1)
				single_check = 0;
			else
				single_check = 1;
		}
		if (line[index] == '"')
		{
			if (double_check == 1)
				double_check = 0;
			else
				double_check = 1;
		}
		index++;
	}
	printf("double%d\nsingle%d\n", double_check, single_check);
	if (double_check == 1 || single_check == 1)
		return (-1);
	return (0);
}
