/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:06:58 by user42            #+#    #+#             */
/*   Updated: 2021/06/26 18:52:26 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_export(t_v *v)
{
	printf("bash: export: '%s': not a validid\n", v->cmd.cmd_args[2]);
	set_return_status(v, EXIT_FAILURE);
}

void	export_var(t_v *v, int len_arr, int i)
{
	char	**new;
	char	**aux;

	if (v->cmd.cmd_args[1] != 0 && ft_count_words(v->cmd.cmd_args[1], '=') != 1)
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
			init_path(v);
		set_return_status(v, EXIT_SUCCESS);
	}
	else
		error_export(v);
}
