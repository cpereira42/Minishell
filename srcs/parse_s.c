/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:33:13 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:06:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_s(t_v *v, char *linha)
{
	int						i;
	int						j;
	t_estado_parse_s		estado;

	v->expandido = (char*)ft_calloc(MIL, sizeof(char));
	estado = NORMAL;
	i = 0;
	j = 0;
	while (linha[i] != 0)
	{
		parse_sq(linha[i], &i, &estado);
		parse_dq(linha[i], &i, &estado);
		if (ft_is_in(linha[i], "$") &&
			(estado == NORMAL || estado == DOUBLE_QUOTE))
			expande(v, &linha[i], &i, &j);
		else
		{
			ft_memcpy(&v->expandido[j], &linha[i], 2);
			j++;
		}
		i++;
	}
	//printf("expandido: |%s|\n", v->expandido);
	return (0);
}
