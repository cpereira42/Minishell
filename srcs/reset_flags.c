/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:14:09 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 18:52:18 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_flags(t_v *v)
{
	v->curr_comand = ft_strdup("");
	v->qtd_hist = 0;
	v->savein = dup(STDIN_FILENO);
	v->saveout = dup(STDOUT_FILENO);
	v->in_fd = STDIN_FILENO;
	v->cmd.ret_status = EXIT_SUCCESS;
	v->r_command = 0;
	v->ret2 = ft_strdup("");
	v->prompt = ft_strdup("");
	v->posic_string = 0;
	v->pid = getpid();
	printf("pid %d\n", v->pid);
	ft_putstr_fd("\033[1;33mBem vindo ao ", 1);
	ft_putstr_fd("MINISHELL CPEREIRA & PCUNHA \033[0;37m\n", 1);
	config_term(v);
}
