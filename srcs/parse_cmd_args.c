/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:06:16 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 19:02:59 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_args(t_v *v, int *k)
{
	char	*cmdeargs;
	char	aux[MIL];

	ft_bzero(aux, MIL);
	copy_until(aux, v->expanded, "<>", k);
	cmdeargs = ft_strtrim(aux, " ");
	v->cmd.cmd_args = ft_split3(cmdeargs, ' ');
	v->cmd.filename = ft_strdup(v->cmd.cmd_args[0]);
	free(cmdeargs);
}
