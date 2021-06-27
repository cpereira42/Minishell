/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 00:42:52 by user42            #+#    #+#             */
/*   Updated: 2021/06/26 18:43:37 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_var_content(t_v *v, char **substr, int q)
{
	*substr = ft_strchr(v->env[q], '=');
	if (ft_strlen(*substr) > 0)
		(*substr)++;
}

int	handle_interr(int r, char c, char **substr, int *k)
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
	char	*substr;

	line++;
	substr = 0;
	v->k = 0;
	v->ax2 = handle_interr(v->cmd.ret_status, line[v->k], &substr, &v->k);
	if (v->ax2 == 0)
	{
		while (!(ft_is_in(line[v->k], " \'\"><")) && v->k < (int)ft_strlen(line))
			v->k++;
		v->q = -1;
		while (v->env[++v->q] != 0)
			if (!ft_strncmp(line, v->env[v->q], v->k))
				substr = loc_var(line, v);
		if (v->ax2 == 1)
		{
			substr = ft_strdup(" ");
			printf("\n");
		}
	}
	ft_memcpy(&v->expanded[(*j)], substr, ft_strlen(substr));
	(*j) = (*j) + ft_strlen(substr);
	(*i) = (*i) + v->k;
	if (v->ax2 == 1)
		free(substr);
}
