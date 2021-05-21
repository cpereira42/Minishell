/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_left.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:43:27 by user42            #+#    #+#             */
/*   Updated: 2021/05/18 19:17:19 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	k_left(t_v *v)
{
	(void) v;
	if (v->posic_string > 0)
			v->posic_string--;
	tputs(tgoto(tgetstr("ch", NULL), 0, v->posic_string + (int)ft_strlen(v->prompt)), 0, &my_termprint);
	tputs(save_cursor,1,my_termprint);

}
