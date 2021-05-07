/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 20:19:00 by user42            #+#    #+#             */
/*   Updated: 2021/05/06 00:23:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_echo(t_v *v)
{
	int	i;
	int	k;

	if (v->cmd.cmd_args[1] != NULL)
	{
		i = 1;
		while (v->cmd.cmd_args[i] != 0)
		{
			k = 0;
			if (i > 1 && v->cmd.cmd_args[i][k] != 0)
				ft_putchar(' ');
			while (v->cmd.cmd_args[i][k] != 0)
			{
				if (v->cmd.cmd_args[i][k] != '"' &&
					v->cmd.cmd_args[i][k] != '\'')
					ft_putchar(v->cmd.cmd_args[i][k]);
				k++;
			}
			i++;
		}
		ft_putchar('\n');
		set_return_status(v, EXIT_SUCCESS);
	}
}
