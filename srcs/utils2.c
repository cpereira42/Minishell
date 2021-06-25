/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:09:36 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/24 17:09:57 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_bksp(t_v *all, int posic)
{
	int	i;

	i = 0;
	posic = posic - 2;
	while (all->ret2[i] != 0)
	{
		if (i > posic)
			all->ret2[i] = all->ret2[i + 1];
		else
			all->ret2[i] = all->ret2[i];
		i++;
	}
	all->ret2[i + 1] = 0;
}
