/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:42:28 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 19:28:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	k_right(t_v *v)
{
	(void) v;
	tputs(restore_cursor,1,my_termprint);
	tputs(tigetstr("ri"),1,my_termprint); // ed
	//ft_putstr_fd("cc",1);
	//ft_bzero(ret,2048);
	//ret2 = ft_strdup("");
	//write (1,"dir\n",3);
}
