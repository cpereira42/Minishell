/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:41:53 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 19:14:57 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	parse_cmd_lines(t_v *v, char *linha)
{
	char	**aux;
	char	*s;
	int		n;

	v->cmd = (t_cmd){0};
	aux = ft_split3(linha, ';');
	n = ft_count_lines(aux);
	//v->cmd_lines = (char **)malloc(sizeof(char *) * (n + 1));
	v->cmd_lines = (char **)safe_malloc(sizeof(char *) * (n + 1));
	int i = 0;
	while(aux[i] && v->flag_exit == 0)
	{
		s = ft_strdup(aux[i]);
		v->cmd_lines[i] = ft_strtrim(s, " ");
		//printf("===============================\n");
		//printf("parsing pipelines ... \n");
		//printf("===============================\n");
		parse_pipelines(v, v->cmd_lines[i]);
		u_free_array_bi(v->pipelines);
		free(s);
		i++;
	}
	v->cmd_lines[i] = 0;
	int z;
	z = 0;
	/*while (z < n)
	{
		free(v->cmd_lines[z]);
		z++;
	}*/
	free_array((void *)v->cmd_lines );
	//free(v->cmd_lines);

	//
	u_free_array_bi(aux);
	return (0);
}
