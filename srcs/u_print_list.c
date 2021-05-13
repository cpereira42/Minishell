/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:15:40 by user42            #+#    #+#             */
/*   Updated: 2021/04/09 17:52:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prints(void *s)
{
	printf("%s\n", (char*)s);
}

void	u_print_list(t_list *list)
{
	while (list)
	{
		prints(list->content);
		list = list->next;
	}
}

void	u_print_dlist(t_dlist *list)
{
	while (list)
	{
		prints(list->content);
		list = list->next;
	}
}
