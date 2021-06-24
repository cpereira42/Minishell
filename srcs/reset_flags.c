/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:14:09 by user42            #+#    #+#             */
/*   Updated: 2021/06/23 17:29:45 by cpereira         ###   ########.fr       */
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
	v->pos_str = 0;
	v->pid = getpid();
	ft_putstr_fd("\033[1;33mWelcome ", 1);
	ft_putstr_fd("MINISHELL CPEREIRA & PCUNHA \033[0;37m\n", 1);
}

void	configs(t_v *v, char **envp)
{
	init_env(v, envp);
	init_path(v);
	reset_flags(v);
	config_term(v);
	if (v->qtd_hist == 0)
		add_samples(v);
	create_prompt(v);
	write_prompt(v);
	v->flag_perm_denied = 0;
}
