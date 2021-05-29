/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 01:52:30 by user42            #+#    #+#             */
/*   Updated: 2021/05/27 20:13:40 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_handler(t_v *v, int i, int n)
{
	int	k;

	k = 0;
	while (v->expanded[k] != 0)
	{
		if (v->expanded[k] == '\"')
			parse_quote_in_redirect(v, &k, "\"");
		else if (v->expanded[k] == '\'')
			parse_quote_in_redirect(v, &k, "\'");
		else if (v->expanded[k] == '<')
			parse_in_red(v, &k, v->cmd.fd_in);
		else if (v->expanded[k] == '>')
			parse_out_red(v, &k, v->cmd.fd_out);
		else if (v->expanded[k] == SPC)
			ff(v->expanded, &k);
		else
			parse_cmd_args(v, &k);
	}
	if (i == 0 && v->cmd.fd_in_red == -1)
		v->cmd.fd_in = STDIN_FILENO;
	if (i == (n - 1) && v->cmd.fd_out_red == -1)
		v->cmd.fd_out = STDOUT_FILENO;
}
