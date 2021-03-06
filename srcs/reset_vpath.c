/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_vpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 01:14:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 02:37:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_vpath(t_v *v)
{
	u_free_array_bi(v->path);
	v->path = (char **)safe_malloc(sizeof(char *) * 2);
	v->path[0] = ft_strdup("");
	v->path[1] = NULL;
}
