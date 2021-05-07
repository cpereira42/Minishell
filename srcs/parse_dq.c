/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:37:55 by user42            #+#    #+#             */
/*   Updated: 2021/04/19 00:39:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dq(char c, int *i, t_estado_parse_s *estado)
{
	(void)i;
	if (ft_is_in(c, "\""))
	{
		if (*estado == NORMAL)
			*estado = DOUBLE_QUOTE;
		else if (*estado == DOUBLE_QUOTE)
			*estado = NORMAL;
		//(*i)++;
		//if (*estado == SINGLE_QUOTE)
		//	(*i)--;
	}
}

