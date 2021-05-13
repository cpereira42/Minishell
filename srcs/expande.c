/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:42:52 by user42            #+#    #+#             */
/*   Updated: 2021/05/06 02:08:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_var_content(t_v *v, char **substr, int q)
{
	*substr = ft_strchr(v->env[q], '=');
	if (ft_strlen(*substr) > 0)
		(*substr)++;
}

int	handle_interrogation(int r, char c, char **substr, int *k)
{
	if (ft_is_in(c, "?"))
	{
		*substr = ft_itoa(r);
		(*k)++;
		return (1);
	}
	else
		return (0);
}

void	expande(t_v *v, char *linha, int *i, int *j)
{
	int		k;
	int		q;
	char	*substr;
	int		aux;

	linha++;
	substr = 0;
	k = 0;
	aux = handle_interrogation(v->cmd.ret_status, linha[k], &substr, &k);
	if (aux == 0)
	{
		while (!(ft_is_in(linha[k], " \'\"><")) && k < (int)ft_strlen(linha))
			k++;
		q = -1;
		while (v->env[++q] != 0)
		{
			if (!ft_strncmp(linha, v->env[q], k))
				get_var_content(v, &substr, q);
		}
	}
	ft_memcpy(&v->expandido[(*j)], substr, ft_strlen(substr));
	(*j) = (*j) + ft_strlen(substr);
	(*i) = (*i) + k;
	if (aux == 1)
		free(substr);
}
