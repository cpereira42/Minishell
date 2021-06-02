/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:41:53 by user42            #+#    #+#             */
/*   Updated: 2021/06/01 20:46:40 by cpereira         ###   ########.fr       */
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

void	init_cmd_args(t_v *v)
{
	v->cmd = (t_cmd){0};
	v->cmd.cmd_args = (char **)safe_malloc((0 + 2) * sizeof(char *));
	//v->cmd.cmd_args[0] = ft_strdup("paulo");
	//v->cmd.cmd_args[1] = ft_strdup("cunha");
	v->cmd.cmd_args[0] = NULL;
}

int	parse_cmd_lines(t_v *v, char *linha, int p)
{
	char	**aux;
	char	*s;
	int		n;
	int		i;
	int		z;
	pid_t	pidf;

	//init_cmd_args(v);
	aux = ft_split3(linha, ';');
	n = ft_count_lines(aux);
	//v->cmd_lines = (char **)malloc(sizeof(char *) * (n + 1));
	//v->cmd_lines = (char **)safe_malloc(sizeof(char *) * (n + 1));
	i = 0;
	p = 0;
	z = 0;
	printf("ola\n");
	//printf("frase inteira = %s\n",linha);
	while(aux[i] && v->flag_exit == 0)
	{
		init_cmd_args(v);
		//aux[i] = ft_strtrim(aux[i],"\"");
		if (ft_strlen(aux[i]) > 0)
		{
			check_n_free(v->curr_comand);
			v->curr_comand = ft_strdup(aux[i]);
			s = ft_strdup(aux[i]);
			v->cmd_lines[i] = ft_strtrim(s, " ");
			if (ft_strlen(v->cmd_lines[i]) > 0)
			{
				parse_pipelines(v, v->cmd_lines[p]);
				u_free_array_bi(v->pipelines);
				p++;
			}
			free(s);
			if (v->cmd.ret_status == -1)
			{
				write_error(v);
				free(v->curr_comand);
				ft_bzero(v->ret,2048);
				pidf = getpid();
				kill(pidf, SIGKILL);
			}
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
}

/*int	parse_cmd_lines(t_v *v, char *linha, int p)
{
	char	**aux;
	char	*s;
	int		n;
	int		i;
	int		z;
	pid_t	pidf;

	//init_cmd_args(v);
	aux = ft_split3(linha, ';');
	n = ft_count_lines(aux);
	//v->cmd_lines = (char **)malloc(sizeof(char *) * (n + 1));
	v->cmd_lines = (char **)safe_malloc(sizeof(char *) * (n + 1));
	i = 0;
	p = 0;
	z = 0;
	printf("ola\n");
	//printf("frase inteira = %s\n",linha);
	while(aux[i] && v->flag_exit == 0)
	{
		init_cmd_args(v);
		//aux[i] = ft_strtrim(aux[i],"\"");
		if (ft_strlen(aux[i]) > 0)
		{
			check_n_free(v->curr_comand);
			v->curr_comand = ft_strdup(aux[i]);
			s = ft_strdup(aux[i]);
			v->cmd_lines[i] = ft_strtrim(s, " ");
			if (ft_strlen(v->cmd_lines[i]) > 0)
			{
				parse_pipelines(v, v->cmd_lines[p]);
				u_free_array_bi(v->pipelines);
				p++;
			}
			free(s);
			if (v->cmd.ret_status == -1)
			{
				write_error(v);
				free(v->curr_comand);
				ft_bzero(v->ret,2048);
				pidf = getpid();
				kill(pidf, SIGKILL);
			}
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
}*/
