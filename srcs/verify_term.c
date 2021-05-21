/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:25:26 by user42            #+#    #+#             */
/*   Updated: 2021/05/18 19:03:35 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int verify_term(t_v *v, char *ret)
{

	if (!ft_strncmp("\e[A",ret,3)) // cima
	{
		k_up(v);
		ret[0] = 0;
		return (1);
	}
	if (!ft_strncmp("\e[B",ret,3)) // baixo
	{
		k_dn(v);
		ret[0] = 0;
		return (1);
	}
	if (!ft_strncmp("\e[C",ret,3)) //  direita
	{
		k_right(v);
		ret[0] = 0;
		return (1);
	}
	else if (!ft_strncmp("\e[D",ret,3)) //  esquerda
	{
		k_left(v);
		ret[0] = 0;
		return (1);
	}
	if (ret[0] == 127) //backspace
	{
		k_bspace(v);
		return (1);
	}
	if (ret[0] == 3) // CTRL+C
		k_ctrl_c(v);
	if (ret[0] == 4) // CTRL +D
		exit_msh(v);
	return (0);
}
