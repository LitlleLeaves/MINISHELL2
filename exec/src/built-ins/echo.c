/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:04:24 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/30 13:37:37 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exho with no arguments
int	ft_echo_no_arguments(void)
{
	printf("\n");
	return (0);
}

//check funtion if there is a 0n, newline option
int	ft_check_echo_option(char **arguments)
{
	if (strncmp(arguments[1], "-n", 3) == 0)
		return (2);
	return (1);
}

//echo funtion prints all words with spaces inbetween, no newline
int	ft_echo_no_newline(char **arguments, int i)
{
	while (arguments[i] != NULL && ft_strncmp(arguments[i], "-n", 3) == 0)
	{
		i++;
	}
	while (arguments[i] != NULL && arguments[i + 1] != NULL)
	{
		printf("%s ", arguments[i]);
		i++;
	}
	if (arguments[i] != NULL)
		printf("%s", arguments[i]);
	return (0);
}

//echo funciton prints all words with spaces with newline
int	ft_echo_newline(char **arguments, int i)
{
	while (arguments[i] != NULL && arguments[i + 1] != NULL)
	{
		printf("%s ", arguments[i]);
		i++;
	}
	if (arguments[i] != NULL)
		printf("%s\n", arguments[i]);
	else
		printf("\n");
	return (0);
}
