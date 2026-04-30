/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:03:44 by jjhurry           #+#    #+#             */
/*   Updated: 2025/05/13 12:03:44 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//sets n addresses to 0 starting at str
void	ft_bzero(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}

static char	*find_in_buffer(char *buffer)
{
	size_t		i;
	char		*str;
	size_t		len;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		i++;
	}
	i++;
	len = i;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*read_buffer(int fd, char	*left, ssize_t *read_bytes)
{
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (free_left(&left));
	*read_bytes = 1;
	while (*read_bytes > 0)
	{
		ft_bzero(buffer);
		*read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*read_bytes < 0)
			return (free(buffer), free_left(&left), NULL);
		else if (*read_bytes == 0)
			return (free(buffer), left);
		left = ft_strjoin(left, buffer);
		if (left == NULL)
			return (free(buffer), NULL);
		if (ft_strchr(left, '\n'))
			break ;
	}
	return (free(buffer), left);
}

static char	*trim_left(char *left)
{
	size_t		i;
	char		*tmp;
	size_t		j;

	i = 0;
	while (left[i] != '\n' && left[i] != '\0')
		i++;
	if (left[i] == '\0' && left[0] == '\0')
		return (free_left(&left), NULL);
	tmp = ft_calloc(ft_strlen(left + i) + 1, 1);
	if (!tmp)
		return (free_left(&left), NULL);
	j = 0;
	if (left[i] != '\0')
		i++;
	while (left[i])
	{
		tmp[j] = left[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (free(left), tmp);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*res;
	ssize_t		read_bytes;

	if (left == NULL)
		left = ft_calloc(1, 1);
	if (!left)
		return (NULL);
	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_left(&left));
	if (!ft_strchr(left, '\n'))
		left = read_buffer(fd, left, &read_bytes);
	if (!left)
		return (NULL);
	if (left[0] == '\0' && read_bytes == 0)
		return (free_left(&left));
	res = find_in_buffer(left);
	if (!res)
		return (free_left(&left));
	left = trim_left(left);
	if (!left)
		return (free(res), free_left(&left));
	return (res);
}
