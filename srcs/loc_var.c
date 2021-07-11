/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:54:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 23:39:08 by pcunha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loc_var(char *var, t_v *v)
{
	int		i;
	int		n;
	char	*aux;

	n = ft_strlen(var);
	i = 0;
	aux = (char *)safe_malloc(sizeof(char *) * (n + 1));
	while (var[i] != 0)
	{
		aux[i] = var[i];
		i++;
	}
	aux[i] = '=';
	aux[i + 1] = 0;
	while (v->env[i] != NULL && ft_strncmp(v->env[i], aux, n + 1))
		i++;
	free(aux);
	if (v->env[i] != NULL)
		return (&v->env[i][n + 1]);
	v->ax2 = 1;
	return ("");
}
