/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:54:08 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 01:01:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *loc_var (char *var, t_v *v)
{
	int i;
	int	n;

	n = ft_strlen(var);
	i = 0;
	while (v->env[i] != NULL && ft_strncmp(v->env[i], var, n))
		i++;
	if (v->env[i] != NULL)
		return(&v->env[i][n + 1]);
	return ("");
}
