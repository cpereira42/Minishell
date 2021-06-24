/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:16:22 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/23 17:16:42 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(t_v *v)
{
	ft_putstr_fd("bash : ", 1);
	ft_putstr_fd(v->curr_comand, 1);
	v->flag_exit = 1;
	ft_putstr_fd(" : command not found\n", 1);
}

void	write_return(t_v *v)
{
	ft_putstr_fd("zsh : command not found : ", 1);
	if (v->cmd.ret_status == 9)
		v->cmd.ret_status = 127;
	ft_putnbr_fd(v->cmd.ret_status, 1);
	ft_putstr_fd("\n", 1);
	v->ret_last = 1;
}

void	write_prompt(t_v *v)
{
	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd(v->prompt, 1);
	ft_putstr_fd("\033[0;37m", 1);
	tputs(tigetstr("ce"), 1, my_termprint);
	tputs(save_cursor, 1, my_termprint);
}
