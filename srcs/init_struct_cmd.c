/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:10:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/06 02:19:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_cmd(t_v *v)
{
	v->cmd.filename = 0;
	v->cmd.cmd_args = 0;
	v->cmd.fd_in_red = -1;
	v->cmd.fd_out_red = -1;
	v->cmd.fd_in = -1;
	v->cmd.fd_out = -1;
	//v->cmd.ret_status = EXIT_SUCCESS;
}
