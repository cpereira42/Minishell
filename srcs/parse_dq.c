/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:37:55 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:41:58 by cpereira         ###   ########.fr       */
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
