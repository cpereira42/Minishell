/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:13:36 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 04:37:06 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_hist(t_v *all, char *ret)
{
	all->posic_hist = all->qtd_hist;
	all->posic_string = 0;
	all->flag_exit = 0;
	all->hist[all->qtd_hist] = malloc((2048 + 1) * sizeof(char*));
	ft_memcpy(all->hist[all->qtd_hist],ret,ft_strlen(ret));
	all->hist[all->qtd_hist][ft_strlen(ret)]= '\0';
	all->posic_hist = all->qtd_hist;
	all->qtd_hist++;
}
