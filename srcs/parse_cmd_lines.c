/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:41:53 by user42            #+#    #+#             */
/*   Updated: 2021/06/20 17:54:25 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	kill_pid(t_v *v)
{
	if (v->cmd.ret_status == -1)
	{
		write_error(v);
		free(v->curr_comand);
		ft_bzero(v->ret, 2048);
		v->pidc = getpid();
		kill(v->pidc, SIGKILL);
	}
}

void	exec_parse_cmd(t_v *v, char **aux, int i, int p)
{
	char	*s;

	check_n_free(v->curr_comand);
	v->curr_comand = ft_strdup(aux[i]);
	s = ft_strdup(aux[i]);
	v->cmd_lines[i] = ft_strtrim(s, " ");
	parse_pipelines(v, v->cmd_lines[p]);
	u_free_array_bi(v->pipelines);
	free(s);
	p++;
	kill_pid(v);
}


int	parse_cmd_lines(t_v *v, char *linha, int p)
{
	char	**aux;
	char	*s;
	int		n;
	int		i;
	int		z;

	aux = ft_split3(linha, ';');
	n = ft_count_lines(aux);
	v->cmd_lines = (char **)safe_malloc(sizeof(char *) * (n + 1));
	i = 0;
	p = 0;
	z = 0;
	while(aux[i] && v->flag_exit == 0)
	{
		if (ft_strlen(aux[i]) > 0)
		{
			//check_n_free(v->curr_comand);
			//v->curr_comand = ft_strdup(aux[i]);

			s = ft_strdup(aux[i]);
			v->cmd_lines[p] = ft_strtrim(s, " ");
			parse_pipelines(v, v->cmd_lines[p]);
			u_free_array_bi(v->pipelines);
			free(s);
			p++;
		}
		i++;
	}
	v->cmd_lines[p] = 0;
	while (z < p )
	{
		free(v->cmd_lines[z]);
		z++;
	}
	free(v->cmd_lines);
	u_free_array_bi(aux);
	return (0);
	/*char	**aux;
	int		i;
	char	*s;

	//v->cmd = (t_cmd){0};
	aux = ft_split3(linha, ';');
	v->cmd_lines = (char **)safe_malloc(sizeof(char *)
			* (ft_count_lines(aux) + 1));
	i = 0;
	while (aux[i] && v->flag_exit == 0)
	{
		if (ft_strlen(aux[i]) > 0)
		{
			init_cmd_args(v);
			check_n_free(v->curr_comand);
			v->curr_comand = ft_strdup(aux[i]);
			s = ft_strdup(aux[i]);
			v->cmd_lines[i] = ft_strtrim(s, " ");
			parse_pipelines(v, v->cmd_lines[p]);
			u_free_array_bi(v->pipelines);
			free(s);
			p++;
			if (v->cmd.ret_status == -1)
			{
				write_error(v);
				free(v->curr_comand);
				ft_bzero(v->ret,2048);
				v->pidc = getpid();
				kill(v->pidc, SIGKILL);
			}
		}
		i++;
	}
	v->cmd_lines[p] = 0;
	i = 0;
	while (i < p)
	{
		free(v->cmd_lines[i]);
		i++;
	}
	free(v->cmd_lines);
	u_free_array_bi(aux);
	return (0);*/
}
