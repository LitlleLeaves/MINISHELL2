/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:19:48 by side-lan          #+#    #+#             */
/*   Updated: 2026/04/15 17:55:23 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//different strjoin!!!
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		len1;
// 	int		len2;
// 	char	*new_str;
// 	int		counter;

// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	new_str = malloc((len1 + len2) + 1);
// 	if (!new_str)
// 		return (NULL);
// 	counter = 0;
// 	while (s1[counter] != '\0')
// 	{
// 		new_str[counter] = s1[counter];
// 		counter++;
// 	}
// 	counter = 0;
// 	while (s2[counter] != '\0')
// 	{
// 		new_str[counter + len1] = s2[counter];
// 		counter++;
// 	}
// 	new_str[counter + len1] = '\0';
// 	return (new_str);
// }

//char	*ft_strdup(char const *str)
//{
//	char	*new;
//	int 	counter;
//	int		size;

//	if (!str)
//		return (printf("empty string"), NULL);
//	size = ft_strlen(str);
//	counter = 0;
//	new	= malloc(sizeof(char) * size);
//	if (!new)
//		return (printf("malloc error"), NULL);
	
//	while (str[counter] != '\0')
//	{
//		new[counter] = str[counter];
//		counter++;
//	}
//	new[counter] = '\0';
//	return (new);
//}

// char	*ft_strdup(const char *s)
// {
// 	int		size;
// 	char	*str;
// 	int		i;

// 	if (!s)
// 		return (NULL);
// 	size = ft_strlen(s);
// 	str = malloc(sizeof(char) * (size + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// int		ft_strlen(char const *str)
// {
// 	int counter;

// 	counter = 0;
// 	while (str[counter] != '\0')
// 		counter++;
// 	return (counter);
// }

// char	*ft_substr(char const *str, int start, int length)
// {
// 	char	*new;
// 	int		counter;
// 	int		str_len;

// 	counter = 0;
// 	if (!str)
// 		return (printf("bad input\n"), NULL);
// 	str_len = ft_strlen(str);
// 	if (start > str_len)
// 		return (ft_strdup(""));
// 	if (start + length > str_len)
// 		new = (char *)malloc((str_len - start) + 1);
// 	else
// 		new = (char *)malloc(length + 1);
// 	if (!new)
// 		return (printf("malloc error"), NULL);
// 	while (counter < length && str[start + counter] != '\0')
// 	{
// 		new[counter] = str[start + counter];
// 		counter++;
// 	}
// 	new[counter] = '\0';
// 	return (new);
// }
