/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 02:04:22 by user42            #+#    #+#             */
/*   Updated: 2021/04/09 17:51:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	u_free_list(t_list *list)
{
	t_list	*aux;

	printf("FREE LISTA LIGADA !!!!\n");
	while (list)
	{
		aux = list;
		list = list->next;
		free(aux);
	}
}

void	u_free_dlist(t_dlist *list)
{
	t_dlist	*aux;

	while (list)
	{
		aux = list;
		list = list->next;
		free(aux);
	}
}
