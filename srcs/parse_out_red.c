/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_out_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 01:57:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:41:15 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_out_red(t_v *v, int *k, int out)
{
	char	file_redir[MIL];
	int		flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	ft_bzero(file_redir, MIL);
	ff(v->expanded, k);
	if (v->expanded[*k] == '>')
	{
		ff(v->expanded, k);
		flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	copy_until(file_redir, v->expanded, " <>", k);
	v->cmd.fd_out_red = open(file_redir, flags, 0777);
	dup2(v->cmd.fd_out_red, out);
	close(v->cmd.fd_out_red);
}
