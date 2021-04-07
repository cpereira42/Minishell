/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:26:45 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/06 18:55:45 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

void	reseta_flags(t_all *all, char **env)
{
	all->ret2 = ft_strdup("");
	all->size = pathconf(".", _PC_PATH_MAX);
	all->buf = (char *)malloc((size_t)all->size);
	all->local = getcwd(all->buf, (size_t)all->size);
	all->ret_split = ft_split(all->ret2,' ');
	all->var_ambiente = get_export(env,all->ret_split);
	all->qtd_hist = 0;
	all->l = 0;
}
