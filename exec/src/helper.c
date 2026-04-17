/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helper.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/10 12:02:36 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/17 13:54:19 by jjhurry       ########   odam.nl         */
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

//compare string 1 and 2 and return the difference for n number of characters, if there is no difference, return 0;
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

//returns 1 if char is a digit, else returns 0
int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

//return 1 if char is alphabetic, els e returns 0
int	ft_isalpha(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		return (1);
	return (0);
}


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

int		check_delimeters(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\0')
		return (1);
	return (0);
}
