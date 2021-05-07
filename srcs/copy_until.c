/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_until.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 00:13:47 by user42            #+#    #+#             */
/*   Updated: 2021/04/12 03:01:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_until(char *dest, char *source, char *delimiters, int *k)
{
	int i;

	i = 0;
	while ((*k + i) < (int)ft_strlen(source) && !ft_is_in(source[*k + i], delimiters))
		i++;
	ft_memcpy(dest, &source[*k], i);
	*k += i;
}
