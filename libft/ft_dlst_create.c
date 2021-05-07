/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:10:04 by user42            #+#    #+#             */
/*   Updated: 2021/04/01 18:43:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlst_create(void *content)
{
	t_dlist *a;

	a = (t_dlist *)malloc(sizeof(t_dlist));
	if (a == NULL)
		return (NULL);
	(*a).content = content;
	(*a).next = NULL;
	(*a).prev = NULL;
	return (a);
}
