/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:28:12 by cpereira         ###   ########.fr       */
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
