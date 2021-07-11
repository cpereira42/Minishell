/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 01:52:30 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 18:12:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_handler(t_v *v, int i, int n)
{
	int	k;

	pipe(v->cmd.pipe);
	v->cmd.fd_out = v->cmd.pipe[PIPE_IN];
	k = 0;
	parse_block(v);
	if (i == 0 && v->cmd.fd_in_red == -1)
		v->cmd.fd_in = STDIN_FILENO;
	if (i == (n - 1) && v->cmd.fd_out_red == -1)
		v->cmd.fd_out = STDOUT_FILENO;
}
