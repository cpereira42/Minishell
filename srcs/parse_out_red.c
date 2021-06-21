/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_out_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 01:57:38 by user42            #+#    #+#             */
/*   Updated: 2021/06/08 21:15:12 by user42           ###   ########.fr       */
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
	if (v->cmd.fd_out_red == -1)
	{
		printf("zsh: permission denied: %s\n", file_redir);
		v->flag_perm_denied = 1;
		v->cmd.ret_status = 1;
		//exit_msh(v);
		//bye(v);
	}
	dup2(v->cmd.fd_out_red, out);
	close(v->cmd.fd_out_red);
}
