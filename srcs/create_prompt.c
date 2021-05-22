/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 01:12:31 by user42            #+#    #+#             */
/*   Updated: 2021/05/22 14:52:18 by cpereira         ###   ########.fr       */
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
	//atualiza_prompt
	//char *aux1;
	char *aux;
	char *logname;
	char *pwd;

	logname = loc_var("LOGNAME", v);
	pwd = loc_var("PWD", v);

	free(v->prompt);
	aux = get_last_path(pwd);
	//v->prompt = ft_strjoin("\033[1;34m", v->prompt);
	aux = ft_strjoin(aux,"> ");
	v->prompt = ft_strdup(aux);
	free (aux);
	//v->prompt = ft_strjoin(v->prompt,"\033[0;37m");
	//ft_putstr_fd(v->prompt,1);


	//aux1 = ft_strjoin(logname, " ");
	//aux2 = ft_strjoin(aux1, pwd);
	//free(aux1);

	//aux1 = ft_strjoin(aux2, "$");
	//free(aux2);

	//v->prompt = ft_strdup(aux1);

	//free(aux1);
}
