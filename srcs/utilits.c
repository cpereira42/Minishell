/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:14:43 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/23 08:41:49 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_lines(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	copy_until(char *dest, char *source, char *delimiters, int *k)
{
	int i;

	i = 0;
	while ((*k + i) < (int)ft_strlen(source) && !ft_is_in(source[*k + i], delimiters))
		i++;
	ft_memcpy(dest, &source[*k], i);
	*k += i;
}

int	count_split(char	**ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	return (i);
}
