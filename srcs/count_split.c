/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:17:08 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 17:35:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_split(char	**ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	return (i);
}
