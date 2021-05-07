/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_out_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 01:57:38 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_out_red(t_v *v, int *k, int out)
{
	char	file_redir[MIL];
	int		flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	ft_bzero(file_redir, MIL);
	ff(v->expandido, k);
	if (v->expandido[*k] == '>')
	{
		ff(v->expandido, k);
		flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	copy_until(file_redir, v->expandido, " <>", k);
	v->cmd.fd_out_red = open(file_redir, flags, 0777);
		//dprintf(v->cmd.save_out, "%s %s\n", file_redir, strerror(errno));
		//errno = 0;
	dup2(v->cmd.fd_out_red, out);
	close(v->cmd.fd_out_red);
}
