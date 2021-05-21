/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:37:55 by user42            #+#    #+#             */
/*   Updated: 2021/05/07 00:59:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dq(char c, int *i, t_state_parse_s *state)
{
	(void)i;
	if (ft_is_in(c, "\""))
	{
		if (*state == NORMAL)
			*state = DOUBLE_QUOTE;
		else if (*state == DOUBLE_QUOTE)
			*state = NORMAL;
	}
}

