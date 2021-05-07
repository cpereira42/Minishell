/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:29:58 by user42            #+#    #+#             */
/*   Updated: 2021/04/09 17:50:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_env(t_v *v, char **envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	while (envp[len_arr])
		len_arr++;
	v->env = (char **)malloc((len_arr + 1) * sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		v->env[i] = ft_strdup(envp[i]);
		i++;
	}
	v->env[i] = 0;
}
