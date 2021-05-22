/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hist2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:00:17 by user42            #+#    #+#             */
/*   Updated: 2021/05/22 12:31:52 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_hist2(t_v *v, char *ret)
{
	int		len_arr;
	int		i;
	char	**new;
	char	**aux;

	len_arr = 0;
	//while (v->hist[len_arr])
	//	len_arr++;
	new = (char **)safe_malloc((v->qtd_hist + 1) * sizeof(char *));
	i = 0;
	while (v->hist[i] != 0)
	{
		new[i] = ft_strdup(v->hist[i]);
		i++;
	}
	new[i] = ft_strdup(ret);
	new[i + 1] = NULL;
	aux = v->hist;
	v->hist = new;
	v->posic_hist = v->qtd_hist;
	v->qtd_hist ++;
	if (aux)
		u_free_array_bi(aux);
	set_return_status(v, EXIT_SUCCESS); // checar se nome da variavel eh valido !
}
