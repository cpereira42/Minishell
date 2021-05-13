/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 01:52:30 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 01:38:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_handler(t_v *v, int i, int n)
{
	int	k;

	k = 0;
	while (v->expandido[k] != 0)
	{
		if (v->expandido[k] == '<')
			parse_in_red(v, &k, v->cmd.fd_in);
		else if (v->expandido[k] == '>')
			parse_out_red(v, &k, v->cmd.fd_out);
		else if (v->expandido[k] == SPC)
			ff(v->expandido, &k);
		else
			parse_cmd_args(v, &k);
	}
	if (i == 0 && v->cmd.fd_in_red == -1)
		v->cmd.fd_in = STDIN_FILENO;
	if (i == (n - 1) && v->cmd.fd_out_red == -1)
		v->cmd.fd_out = STDOUT_FILENO;
}
