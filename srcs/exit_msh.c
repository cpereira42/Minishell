/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 22:58:41 by user42            #+#    #+#             */
/*   Updated: 2021/05/06 17:52:54 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msh(t_v *v)
{
	v->flag_exit = 1;
	set_return_status(v, EXIT_SUCCESS);
	printf("Logout\n");
	tcsetattr(0,TCSANOW,&v->old);
	u_free_array_bi(&v->ret2);
	u_free_array_bi(v->env);
	u_free_array_bi(v->cmd_lines);
	u_free_array_bi(v->path);
	free(v->prompt);
	exit(1);
}
