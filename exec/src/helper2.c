/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:13 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 12:46:31 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *str, int start, int length)
{
	char	*new;
	int		counter;
	int		str_len;

	counter = 0;
	if (!str)
		return (printf("bad input\n"), NULL);
	str_len = ft_strlen(str);
	if (start > str_len)
		return (ft_strdup(""));
	if (start + length > str_len)
		new = (char *)ft_calloc((str_len - start) + 1, sizeof(char));
	else
		new = (char *)ft_calloc(length + 1, sizeof(char));
	if (!new)
		return (printf("malloc error"), NULL);
	while (counter < length && str[start + counter] != '\0')
	{
		new[counter] = str[start + counter];
		counter++;
	}
	new[counter] = '\0';
	return (new);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

//copies n bytes of memory from -> to, does not take overlap in mind
void	*ft_memcpy(void	*to, const void*from, size_t bytes)
{
	size_t			i;
	unsigned char	*res;
	const char		*tmp;

	if (to == NULL && from == NULL)
		return (NULL);
	tmp = from;
	res = to;
	i = 0;
	while (i < bytes)
	{
		res[i] = tmp[i];
		i++;
	}
	return (res);
}

int	check_delimeters(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

//returns 1 if char is a digit, else returns 0
int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}
