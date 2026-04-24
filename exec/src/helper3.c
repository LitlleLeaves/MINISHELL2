/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhurry <jjhurry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:15:01 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/24 12:15:12 by jjhurry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return 1 if char is alphabetic, els e returns 0
int	ft_isalpha(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		return (1);
	return (0);
}
