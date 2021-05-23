/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 01:12:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/22 18:40:12 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_last_path(char *ret)
{
	int i;

	i = ft_strlen(ret);
	while (i > 0)
	{
		if (ret[i] != '/')
			i--;
		else
			break;
	}
	return(&ret[i]);
}

void	create_prompt(t_v *v)
{
	char *aux;
	char *logname;
	char *pwd;

	logname = loc_var("LOGNAME", v);
	pwd = loc_var("PWD", v);
	free(v->prompt);
	aux = get_last_path(pwd);
	aux = ft_strjoin(aux, "> ");
	v->prompt = ft_strdup(aux);
	free (aux);
}
