/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:19:17 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 17:57:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_add(t_dlist **lst, void *a)
{
	t_dlist	*ultimo;
	t_dlist	*new;

	new = ft_dlst_create(a);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ultimo = ft_dlst_last(*lst);
	ultimo->next = new;
	ultimo->prev = ultimo;
}
