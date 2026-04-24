/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:02:36 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 12:40:50 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>
#include <limits.h>

//allocate nmemb amount of data of size size
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

/*compare string 1 and 2 and return the difference for n number of characters,
if there is no difference, return 0;*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*ucs1;
	const unsigned char	*ucs2;
	size_t				i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	ucs1 = (const unsigned char *)s1;
	ucs2 = (const unsigned char *)s2;
	while ((ucs1[i] || ucs2[i]) && i < n)
	{
		if (ucs1[i] != ucs2[i])
			return (ucs1[i] - ucs2[i]);
		i++;
	}
	return (0);
}

//returns the length of string str
size_t	ft_strlen(const char *str)
{
	int	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length])
		length++;
	return (length);
}

/*searches and returns the first instance of char c in str, 
if not found returns NULL*/
char	*ft_strchr(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == (unsigned char) c)
			return ((char *) str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *) str);
	return (NULL);
}

//returns a copy of str s
char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
