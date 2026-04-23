/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/12 14:04:46 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 11:17:03 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "exec.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen((char *)src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(dst);
	if (size <= len)
		return (size + ft_strlen((char *)src));
	while (len < size - 1 && *src)
	{
		dst[len] = *src;
		src++;
		len++;
	}
	dst[len] = '\0';
	return (len + ft_strlen((char *)src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(str, s2, len + 1);
	str[len] = '\0';
	return (str);
}
