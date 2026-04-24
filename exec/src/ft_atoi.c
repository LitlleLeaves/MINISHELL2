/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:33:55 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 14:34:17 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int static	ft_atoi_help(const char *ptr)
{
	int	number;

	number = 0;
	while (*ptr >= '0' && *ptr <= '9')
	{
		number = (number * 10) + *ptr - '0';
		ptr++;
	}
	return (number);
}

//converts a string with possible issapce char and sign char to integer
int	ft_atoi(const char *ptr)
{
	int	sign;

	sign = 1;
	if (!(*ptr == 32 || *ptr == 43 || *ptr == 45
			|| (*ptr >= '0' && *ptr <= '9') || (*ptr >= 9 && *ptr <= 13)))
		return (0);
	while (*ptr == 32 || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (!(*ptr == 43 || *ptr == 45 || (*ptr >= '0' && *ptr <= '9')))
		return (0);
	if (*ptr == 43 || *ptr == 45)
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	if (!(*ptr >= '0' && *ptr <= '9'))
		return (0);
	return (sign * ft_atoi_help(ptr));
}
