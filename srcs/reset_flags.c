/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:14:09 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 17:15:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_flags(t_v *all)
{
	all->qtd_hist = 0;
	all->savein = dup(STDIN_FILENO);
	all->saveout = dup(STDOUT_FILENO);
	all->in_fd = STDIN_FILENO;
}
