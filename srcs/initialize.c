/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:08:00 by user42            #+#    #+#             */
/*   Updated: 2021/06/24 19:59:26 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path(t_v *v)
{
	char	*aux;

	v->path = NULL;
	aux = loc_var("PATH", v);
	v->path = ft_split(aux, ':');
}

void	init_env(t_v *v, char **envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	while (envp[len_arr])
		len_arr++;
	v->env = (char **)safe_malloc((len_arr + 1) * sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		v->env[i] = ft_strdup(envp[i]);
		i++;
	}
	v->env[i] = 0;
}

void	init_struct_cmd(t_v *v)
{
	v->cmd.fn = 0;
	v->cmd.fd_in_red = -1;
	v->cmd.fd_out_red = -1;
	v->cmd.fd_in = -1;
	v->cmd.fd_out = -1;
	v->cmd.save_in = dup(STDIN_FILENO);
	v->cmd.save_out = dup(STDOUT_FILENO);
	v->cmd.fd_in = STDIN_FILENO;
}

void	init_cmd_args(t_v *v)
{
	v->cmd.cmd_args = (char **)safe_malloc((0 + 1) * sizeof(char *));
	v->cmd.cmd_args[0] = NULL;
}
