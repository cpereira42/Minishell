/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_return_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 00:10:08 by user42            #+#    #+#             */
/*   Updated: 2021/05/06 02:21:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	set_return_status(t_v *v, int status)
{
	if (status == 0)
	{
		v->cmd.ret_status = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	else
	{
		v->cmd.ret_status = status;
		return (status);
	}
}
