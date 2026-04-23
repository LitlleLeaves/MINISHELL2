/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/23 10:31:19 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 11:44:30 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//print declare -x <string> for each env member
int ft_export_print_list(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		printf("declare -x %s\n", data->envp[i]);
		i++;
	}
	return (0);
}
