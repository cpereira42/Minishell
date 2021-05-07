/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 00:12:59 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 01:07:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_com(t_v *v)
{
	int		i;
	char	*comando;
	char	*aux;
	int		r;

	r = -1;
	i = 0;
	while (v->path[i] != NULL)
	{
		aux = ft_strdup(v->path[i]);
		comando = ft_strjoin(aux, "/");
		free(aux);
		aux = comando;
		comando = ft_strjoin(aux, v->cmd.cmd_args[0]);
		r = execve(comando, &v->cmd.cmd_args[0], v->env);
		free(aux);
		free(comando);
		i++;
	}
	return (r);
}
