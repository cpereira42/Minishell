/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print_struct_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:52:20 by user42            #+#    #+#             */
/*   Updated: 2021/06/04 18:25:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	u_print_struct_cmd(t_v *v)
{
	dprintf(v->cmd.save_out,"__________________________________________\n");
	dprintf(v->cmd.save_out,"   STRUCT CMD    \n");
	if (v->cmd.filename != NULL)
		dprintf(v->cmd.save_out,"filename:\t\t|%s|\n", v->cmd.filename);
	else
		dprintf(v->cmd.save_out,"filename:\t\t|vazio|\n");
	dprintf(v->cmd.save_out,"cmd_args:\n");
	u_print_array_bi(v, v->cmd.cmd_args);
	//dprintf(v->cmd.save_out,"|%s|:\n", v->cmd.cmd_args[0]);
	//if (v->cmd.cmd_args[0] != NULL && !strcmp(v->cmd.cmd_args[0], ""))
	//	u_print_array_bi(v, v->cmd.cmd_args);
	//else
	//	dprintf(v->cmd.save_out,"\n");
	dprintf(v->cmd.save_out,"fd_in_red: %d\t\t fd_out_red: %d\n", v->cmd.fd_in_red, v->cmd.fd_out_red);
	dprintf(v->cmd.save_out,"pipe[in]: %d\t\t pipe[out]: %d\n", v->cmd.pipe[PIPE_IN], v->cmd.pipe[PIPE_OUT]);
	dprintf(v->cmd.save_out,"fd_in: %d\t\t fd_out: %d\n", v->cmd.fd_in, v->cmd.fd_out);
	dprintf(v->cmd.save_out,"ret_status:\t\t %d\n",v->cmd.ret_status);
	dprintf(v->cmd.save_out,"__________________________________________\n");
}
