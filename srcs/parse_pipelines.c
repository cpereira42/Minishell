/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipelines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 03:47:00 by user42            #+#    #+#             */
/*   Updated: 2021/05/23 16:19:49 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	parse_pipelines(t_v *v, char *linha)
{
	char	**aux;
	char	*s;
	int		n;
	int		i;
	//char	*x = NULL;

	aux = ft_split3(linha, '|');
	i = 1;
	while(aux[i] != NULL)
	{
		ft_rmvchar(&aux[i],'\"');
		ft_rmvchar(&aux[i],'\'');
		i++;
	}
	n = ft_count_lines(aux);
	v->pipelines = (char **)safe_malloc(sizeof(char *) * (n + 1));
	init_struct_cmd(v);

	//// SALVA STDS
	v->cmd.save_in = dup(STDIN_FILENO);
	v->cmd.save_out = dup(STDOUT_FILENO);

	v->cmd.fd_in = STDIN_FILENO;

	i = 0;
	while(aux[i] && v->flag_exit == 0)
	{
		s = ft_strdup(aux[i]);
		v->pipelines[i] = ft_strtrim(s, " "); // PRECISA DESTA LINHA ???
		parse_s(v, v->pipelines[i]);
		pipe(v->cmd.pipe);
		v->cmd.fd_out = v->cmd.pipe[PIPE_IN];
		redirect_handler(v, i, n);
		fd_handler(v->cmd.fd_in, v->cmd.fd_out);
		execute_command(v);

		// Close stdout e fds e remapeia entrada do proximo !
		close(v->cmd.fd_out);
		if (v->cmd.fd_in != 0)
			close(v->cmd.fd_in);
		v->cmd.fd_in = v->cmd.pipe[PIPE_OUT];
		// restaura fds
		dup2(v->cmd.save_in, STDIN_FILENO);
		dup2(v->cmd.save_out, STDOUT_FILENO);
		//printf("Apos restaura fds\n");
		//u_print_struct_cmd(v);
		// FIM LOOP
		// frees
		free(v->cmd.filename);
		v->cmd.filename = NULL;
		free(v->expanded);
		v->expanded = NULL;
		free(s);
		s = NULL;
		u_free_array_bi(v->cmd.cmd_args);
		i++;
	}

		close(v->cmd.save_in);
		close(v->cmd.save_out);
		close(v->cmd.pipe[0]);
		close(v->cmd.pipe[1]);

	v->pipelines[i] = 0;
	u_free_array_bi(aux);
	return (0);
}
