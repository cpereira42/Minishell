/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:33:13 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:29:44 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_s(t_v *v, char *linha)
{
	int						i;
	int						j;
	t_state_parse_s			state;

	v->expanded = (char *)ft_calloc(MIL, sizeof(char));
	state = NORMAL;
	i = 0;
	j = 0;
	while (linha[i] != 0)
	{
		parse_sq(linha[i], &i, &state);
		parse_dq(linha[i], &i, &state);
		if (ft_is_in(linha[i], "$")
			&& (state == NORMAL || state == DOUBLE_QUOTE))
			expand(v, &linha[i], &i, &j);
		else
		{
			ft_memcpy(&v->expanded[j], &linha[i], 2);
			j++;
		}
		i++;
	}
	return (0);
}
