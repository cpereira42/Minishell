/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:35:17 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:41:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(t_v *v, char *var)
{
	int		i;
	char	*buf;
	char	*aux;
	int		n;

	n = ft_strlen(var);
	buf = NULL;
	buf = getcwd(buf, MIL);
	i = 0;
	while (v->env[i] != NULL && ft_strncmp(v->env[i], var, n))
		i++;
	if (v->env[i] != NULL)
	{
		free(v->env[i]);
		aux = ft_strjoin(var, "=");
		v->env[i] = ft_strjoin(aux, buf);
		free(aux);
	}
	free(buf);
}
