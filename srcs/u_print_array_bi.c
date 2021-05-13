/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print_array_bi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:11:16 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 19:07:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	u_print_array_bi(t_v *v, char **s)
{
	int i;
	int aux;
	(void) aux;

	(void) v;

	if (fcntl(v->cmd.save_out, F_GETFD) != -1)
		aux = v->cmd.save_out;
	else
		aux = 1;


	if (s!= NULL)
	{
		i = 0;
		while (s[i] != 0)
		{
			dprintf(aux,"|%s|\n", (s[i]));
			//dprintf(v->cmd.save_out,"|%s|\n", (s[i]));
			//dprintf(1,"|%s|\n", (s[i]));
			i++;
		}
	}
}
