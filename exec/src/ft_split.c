/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jjhurry <jjhurry@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/12 13:39:33 by jjhurry       #+#    #+#                 */
/*   Updated: 2026/04/23 10:58:48 by jjhurry       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*fill_word(int start, const char *str, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (start < end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

static int	word_count(const char *str, char c)
{
	int	count;
	int	word;

	word = 0;
	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c && word == 0)
		{
			count++;
			word = 1;
		}
		else if (*str == c)
			word = 0;
		str++;
	}
	return (count);
}

static int	init_var(size_t *i, size_t *j, int *start, const char *str)
{
	*i = 0;
	*start = -1;
	*j = 0;
	if (!str)
		return (0);
	return (1);
}

static char	**ft_free_mem(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	return (NULL);
}

/*takes a string str, and returns an string array of 
all words, delimited by c. NULL terminates the array*/
char	**ft_split(const char *str, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	int		start;

	if (!(init_var(&i, &j, &start, str)))
		return (NULL);
	array = (char **)ft_calloc((word_count(str, c) + 1), sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (i <= ft_strlen(str))
	{
		if (str[i] != c && start < 0)
			start = i;
		else if ((str[i] == c || i == ft_strlen(str)) && start >= 0)
		{
			array[j] = fill_word(start, str, i);
			if (array[j] == NULL)
				return (ft_free_mem(array, j));
			start = -1;
			j++;
		}
		i++;
	}
	return (array);
}
