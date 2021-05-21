/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_up.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:39:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/18 19:15:24 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	k_up(t_v *v)
{
	//printf("qtd_hist %d, posic = %d\n",v->qtd_hist,v->posic_hist);
	tputs(restore_cursor,1,my_termprint);
	tputs(tigetstr("ed"),1,my_termprint); //kL
	v->ret2 = ft_strdup(v->hist[v->posic_hist]);
	ft_putstr_fd(v->ret2,1);
	if (v->posic_hist <= 0)
		v->posic_hist = 0;
	else
		v->posic_hist --;
}
