/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 01:12:31 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 01:19:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_prompt(t_v *v)
{
	//atualiza_prompt
	char *aux1;
	char *aux2;
	char *logname;
	char *pwd;

	logname = loc_var("LOGNAME", v);
	pwd = loc_var("PWD", v);
	aux1 = ft_strjoin(logname, " ");
	aux2 = ft_strjoin(aux1, pwd);
	free(aux1);
	aux1 = ft_strjoin(aux2, "$");
	free(aux2);
	v->prompt = ft_strdup(aux1);
	free(aux1);
}
