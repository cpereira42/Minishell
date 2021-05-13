/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/04/19 00:37:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_sq(char c, int *i, t_estado_parse_s *estado)
{
	(void)i;
	if (ft_is_in(c, "\'"))
	{
		if (*estado == NORMAL)
			*estado = SINGLE_QUOTE;
		else if (*estado == SINGLE_QUOTE)
			*estado = NORMAL;
		//(*i)++;
		//if (*estado == DOUBLE_QUOTE)
		//	(*i)--;
	}
}

