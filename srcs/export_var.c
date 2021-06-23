/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:06:58 by user42            #+#    #+#             */
/*   Updated: 2021/06/22 16:23:14 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_var(t_v *v, int len_arr, int i)
{
	char	**new;
	char	**aux;

	if (v->cmd.cmd_args[1] != 0)
	{
		exc_var(v, 0, 0);
		while (v->env[len_arr])
			len_arr++;
		new = (char **)safe_malloc((len_arr + 2) * sizeof(char *));
		while (v->env[i] != 0)
		{
			new[i] = ft_strdup(v->env[i]);
			i++;
		}
		new[i] = ft_strdup(v->cmd.cmd_args[1]);
		new[i + 1] = NULL;
		aux = v->env;
		v->env = new;
		u_free_array_bi(aux);
		if (ft_strncmp(v->cmd.cmd_args[1], "PATH", 4) == 0)
		{
			u_free_array_bi(v->path);
			init_path(v);
		}
	}
	set_return_status(v, EXIT_SUCCESS);
}
