/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:08:00 by user42            #+#    #+#             */
/*   Updated: 2021/05/18 01:18:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_hist(t_v *v, char *envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	v->hist = (char **)safe_malloc((len_arr + 1) * sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		v->hist[i] = ft_strdup(envp);
		i++;
	}
	v->hist[i] = 0;
}
