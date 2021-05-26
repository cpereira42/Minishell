/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:58:59 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:41:41 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_in_red(t_v *v, int *k, int in)
{
	char	file_redir[MIL];

	ft_bzero(file_redir, MIL);
	ff(v->expanded, k);
	copy_until(file_redir, v->expanded, " <>", k);
	v->cmd.fd_in_red = open(file_redir, O_RDONLY | O_CREAT);
	dup2(v->cmd.fd_in_red, in);
	close(v->cmd.fd_in_red);
}
