/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_dn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:41:18 by user42            #+#    #+#             */
/*   Updated: 2021/05/18 19:15:36 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	k_dn(t_v *v)
{
	//printf("qtd_hist %d, posic = %d\n",v->qtd_hist,v->posic_hist);
	tputs(restore_cursor,1,my_termprint);
	tputs(tigetstr("ed"),1,my_termprint);
	v->ret2 = ft_strdup(v->hist[v->posic_hist]);
	ft_putstr_fd(v->ret2,1);
	if (v->posic_hist >= v->qtd_hist - 1)
		v->posic_hist = v->qtd_hist - 1;
	else
		v->posic_hist ++;
}
