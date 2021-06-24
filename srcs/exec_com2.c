/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 00:45:53 by user42            #+#    #+#             */
/*   Updated: 2021/06/23 18:43:07 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cont (t_v *v, int r)
{
	int		i;
	char	*aux;
	char	*command;

	i = 0;
	if (v->cmd.cmd_args[1] != NULL )
		if (v->cmd.cmd_args[1][0] == '~' && v->cmd.cmd_args[1][1] != '~')
			v->cmd.cmd_args[1] = (ft_strjoin(loc_var("HOME", v),
						&v->cmd.cmd_args[1][1]));
	v->cmd.cmd_args[0] = get_last_path2(v->cmd.cmd_args[0]);
	while (v->path[i] != NULL)
	{
		aux = ft_strdup(v->path[i]);
		command = ft_strjoin(aux, "/");
		free(aux);
		aux = command;
		command = ft_strjoin(aux, v->cmd.cmd_args[0]);
		r = execve(command, &v->cmd.cmd_args[0], v->env);
		free(aux);
		free(command);
		i++;
	}
	return (r);
}

int	exec_com2(t_v *v)
{
	int		r;

	if (is_abs_path(v->cmd.cmd_args[0]))
	{
		r = execve(v->cmd.fn, &v->cmd.cmd_args[0], v->env);
		return (r);
	}
	else
	{
		r = execve(v->cmd.fn, &v->cmd.cmd_args[0], v->env);
		if (r > 0)
			return (r);
		else
		{
			if (v->path[0] == NULL)
				return (-1);
			else
			{
				return (exec_cont (v, -1));
			}
		}
	}
}
