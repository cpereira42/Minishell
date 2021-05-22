/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:08:00 by user42            #+#    #+#             */
/*   Updated: 2021/05/22 13:05:23 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_hist(t_v *v, char *envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	//v->hist = (char **)safe_malloc((len_arr + 1) * sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		v->hist[i] = ft_strdup(envp);
		i++;
	}
	v->hist[i] = 0;
}
