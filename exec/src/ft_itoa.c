/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:01:04 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/08 17:01:13 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_number_length(long n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_zero_helper(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

//converts a integer to a string
char	*ft_itoa(int n)
{
	long	num;
	char	*str;
	int		len;

	num = n;
	len = ft_number_length(num);
	if (num == 0)
		return (ft_zero_helper());
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	while (num)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}
