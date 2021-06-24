/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipelines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:47:00 by user42            #+#    #+#             */
/*   Updated: 2021/06/23 19:42:03 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_parse(t_v *v, char *aux, int i, int n)
{
	char	*s;

	s = ft_strdup(aux);
	v->pipelines[i] = ft_strtrim(s, " ");
	parse_s(v, v->pipelines[i]);
	pipe(v->cmd.pipe);
	v->cmd.fd_out = v->cmd.pipe[PIPE_IN];
	redirect_handler(v, i, n);
	fd_handler(v->cmd.fd_in, v->cmd.fd_out);
	execute_command(v);
	close(v->cmd.fd_out);
	if (v->cmd.fd_in != 0)
		close(v->cmd.fd_in);
	v->cmd.fd_in = v->cmd.pipe[PIPE_OUT];
	dup2(v->cmd.save_in, STDIN_FILENO);
	dup2(v->cmd.save_out, STDOUT_FILENO);
	free(v->cmd.fn);
	v->cmd.fn = NULL;
	free(v->expanded);
	v->expanded = NULL;
	free(s);
	s = NULL;
	u_free_array_bi(v->cmd.cmd_args);
}

int	parse_pipelines(t_v *v, char *linha, int i, int n)
{
	char	**aux;
	char	*s;

	aux = ft_split3(linha, '|');
	n = remov_quots(1, aux);
	v->pipelines = (char **)safe_malloc(sizeof(char *) * (n + 1));
	init_struct_cmd(v);
	while (aux[i] && v->flag_exit == 0)
	{
		init_cmd_args(v);
		s = ft_strdup(aux[i]);
		v->pipelines[i] = ft_strtrim(s, " ");
		parse_s(v, v->pipelines[i]);
		redirect_handler(v, i, n);
		fd_handler(v->cmd.fd_in, v->cmd.fd_out);
		check_n_free(v->curr_comand);
		v->curr_comand = ft_strdup(v->cmd.fn);
		if (v->flag_perm_denied == 0)
			execute_command(v);
		dups_clear(v, s);
		i++;
	}
	close_fds(v, i);
	u_free_array_bi(aux);
	return (0);
}

void	dups_clear(t_v *v, char *s)
{
	v->flag_perm_denied = 0;
	close(v->cmd.fd_out);
	if (v->cmd.fd_in != 0)
		close(v->cmd.fd_in);
	v->cmd.fd_in = v->cmd.pipe[PIPE_OUT];
	dup2(v->cmd.save_in, STDIN_FILENO);
	dup2(v->cmd.save_out, STDOUT_FILENO);
	cleaning(v, s);
	verify_ret(v);
}

void	cleaning(t_v *v, char *s)
{
	free(v->cmd.fn);
	v->cmd.fn = NULL;
	free(v->expanded);
	v->expanded = NULL;
	free(s);
	s = NULL;
	u_free_array_bi(v->cmd.cmd_args);
}

void	verify_ret(t_v *v)
{
	pid_t	pidf;

	if (v->cmd.ret_status == -1)
	{
		write_error(v);
		free(v->curr_comand);
		ft_bzero(v->ret, 2048);
		pidf = getpid();
		kill(pidf, SIGKILL);
	}
}
