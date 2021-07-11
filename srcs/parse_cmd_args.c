/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:06:16 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 23:40:18 by pcunha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_quote_in_redirect(t_v *v, int *k, char *c)
{
	char	aux[MIL];

	ft_bzero(aux, MIL);
	ff(v->expanded, k);
	copy_until(aux, v->expanded, c, k);
	add_line_to_cmd_args(v, aux);
	(*k)++;
}

void	add_line_to_cmd_args(t_v *v, char *src)
{
	int		len_arr;
	int		i;
	char	**new;
	char	**aux;

	len_arr = 0;
	while (v->cmd.cmd_args[len_arr])
		len_arr++;
	new = (char **)safe_malloc((len_arr + 2) * sizeof(char *));
	i = 0;
	while (v->cmd.cmd_args[i] != 0)
	{
		new[i] = ft_strdup(v->cmd.cmd_args[i]);
		i++;
	}
	new[i] = ft_strdup(src);
	new[i + 1] = NULL;
	aux = v->cmd.cmd_args;
	v->cmd.cmd_args = new;
	u_free_array_bi(aux);
}

void	parse_cmd_args(t_v *v, int *k)
{
	char	*cmdeargs;
	char	aux[MIL];
	char	**temp;
	int		i;

	ft_bzero(aux, MIL);
	copy_until(aux, v->expanded, "\"\'<>", k);
	cmdeargs = ft_strtrim(aux, " ");
	temp = ft_split3(cmdeargs, ' ');
	i = 0;
	while (temp[i])
	{
		add_line_to_cmd_args(v, temp[i]);
		i++;
	}
	v->cmd.fn = ft_strdup(v->cmd.cmd_args[0]);
	ff_until_char(v->expanded, k, " <>\"\'");
	free(cmdeargs);
	u_free_array_bi(temp);
}
