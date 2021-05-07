/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:06:16 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:06:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_args(t_v *v, int *k)
{
	char *cmdeargs;
	char aux[MIL];

	ft_bzero(aux, MIL);
	copy_until(aux, v->expandido, "<>", k);
	cmdeargs = ft_strtrim(aux, " ");
	v->cmd.cmd_args = ft_split3(cmdeargs, ' ');
		//u_print_array_bi(v, v->cmd.cmd_args);
	v->cmd.filename = ft_strdup(v->cmd.cmd_args[0]);
	free(cmdeargs);
}
