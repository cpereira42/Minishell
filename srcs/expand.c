/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:42:52 by user42            #+#    #+#             */
/*   Updated: 2021/05/23 16:19:10 by cpereira         ###   ########.fr       */
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

void	expand(t_v *v, char *line, int *i, int *j)
{
	int		k;
	int		q;
	char	*substr;
	int		aux;

	line++;
	substr = 0;
	k = 0;
	aux = handle_interrogation(v->cmd.ret_status, line[k], &substr, &k);
	if (aux == 0)
	{
		while (!(ft_is_in(line[k], " \'\"><")) && k < (int)ft_strlen(line))
			k++;
		q = -1;
		while (v->env[++q] != 0)
		{
			if (!ft_strncmp(line, v->env[q], k))
				get_var_content(v, &substr, q);
		}
	}
	write_return(v);
	ft_memcpy(&v->expanded[(*j)], substr, ft_strlen(substr));
	(*j) = (*j) + ft_strlen(substr);
	(*i) = (*i) + k;
	if (aux == 1)
		free(substr);
}
