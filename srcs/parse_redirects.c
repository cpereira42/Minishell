/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:27:17 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:29:54 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirects(t_v *v)
{
	int	k;

	k = 0;
	while (v->expanded[k] != 0)
	{
		if (v->expanded[k] == '<')
			parse_in_red(v, &k);
		else if (v->expanded[k] == '>')
			parse_out_red(v, &k);
		else if (v->expanded[k] == SPC)
			ff(v->expanded, &k);
		else
			parse_cmd_args(v, &k);
	}
}
