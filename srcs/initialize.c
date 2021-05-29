/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:08:00 by user42            #+#    #+#             */
/*   Updated: 2021/05/27 20:12:37 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hist(t_v *v, char *envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	i = 0;
	while (i < len_arr)
	{
		v->hist[i] = ft_strdup(envp);
		i++;
	}
	v->hist[i] = 0;
}

void	init_path(t_v *v)
{
	char	*aux;

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
	v->cmd.filename = 0;
	//v->cmd.cmd_args = 0;
	v->cmd.fd_in_red = -1;
	v->cmd.fd_out_red = -1;
	v->cmd.fd_in = -1;
	v->cmd.fd_out = -1;
	v->cmd.save_in = dup(STDIN_FILENO);
	v->cmd.save_out = dup(STDOUT_FILENO);
	v->cmd.fd_in = STDIN_FILENO;
}
