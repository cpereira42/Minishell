/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/05/07 00:59:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_sq(char c, int *i, t_state_parse_s *state)
{
	(void)i;
	if (ft_is_in(c, "\'"))
	{
		if (*state == NORMAL)
			*state = SINGLE_QUOTE;
		else if (*state == SINGLE_QUOTE)
			*state = NORMAL;
	}
}

