/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:58:13 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 23:39:44 by pcunha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_block(t_v *v)
{
	int	k;

	k = 0;
	while (v->expanded[k] != 0)
	{
		if (v->expanded[k] == ' ')
			ff(v->expanded, &k);
		else if (v->expanded[k] == '\"')
			parse_quote_in_redirect(v, &k, "\"");
		else if (v->expanded[k] == '\'')
			parse_quote_in_redirect(v, &k, "\'");
		else if (v->expanded[k] == '<')
			parse_in_red(v, &k, v->cmd.fd_in);
		else if (v->expanded[k] == '>')
			parse_out_red(v, &k, v->cmd.fd_out);
		else
			parse_cmd_args(v, &k);
	}
}
