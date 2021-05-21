/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:44:36 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 18:51:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	k_bspace(t_v *v)
{
	tputs(restore_cursor,1,my_termprint);
	tputs(tigetstr("ed"),1,my_termprint);
	//tputs(tigetstr("kD"),1,my_termprint);
	v->ret2[ft_strlen(v->ret2)-1] = 0;
	ft_putstr_fd(v->ret2,1);
}
