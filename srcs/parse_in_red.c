/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:58:59 by user42            #+#    #+#             */
/*   Updated: 2021/07/10 21:49:46 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_in_red(t_v *v, int *k, int in)
{
	char	file_redir[MIL];
	int		fd_temp;

	ft_bzero(file_redir, MIL);
	ft_bzero(v->eof, MIL);
	ff(v->expanded, k);
	if (v->expanded[*k] == '<')
	{
		ff(v->expanded, k);
		v->flag_heredoc = 1;
		copy_until(v->eof, v->expanded, " <>", k);
		ft_memcpy(file_redir, "zzzz\0", 5);
		fd_temp = open(file_redir, O_RDWR | O_CREAT | O_TRUNC, 0777);
		handle_heredoc(v, fd_temp);
		close(fd_temp);
	}
	else
	{
		copy_until(file_redir, v->expanded, " <>", k);
	}
	v->cmd.fd_in_red = open(file_redir, O_RDONLY | O_CREAT);
	dup2(v->cmd.fd_in_red, in);
	close(v->cmd.fd_in_red);
}
