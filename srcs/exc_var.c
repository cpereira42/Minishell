/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:30:57 by user42            #+#    #+#             */
/*   Updated: 2021/05/06 00:32:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alocate_new(t_v *v)
{
	int		i;
	char	**new;

	i = 0;
	while (v->env[i])
		i++;
	new = (char **)malloc((i + 1) * sizeof(char *));
	return (new);
}

void	exc_var(t_v *v)
{
	int		i;
	int		k;
	char	**new;
	char	**aux;
	char	*var;

	if (v->cmd.cmd_args[1] != 0)
	{
		var = get_var(v);
		new = alocate_new(v);
		i = 0;
		k = 0;
		while (v->env[i] != 0)
		{
			if (ft_strncmp(v->env[i], var, ft_strlen(var)) != 0)
				new[k++] = ft_strdup(v->env[i]);
			i++;
		}
		new[k] = NULL;
		aux = v->env;
		v->env = new;
		u_free_array_bi(aux);
		free(var);
		set_return_status(v, EXIT_SUCCESS); // Failure se variavel readonly
	}
}
