/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 01:11:30 by user42            #+#    #+#             */
/*   Updated: 2021/05/23 16:29:36 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_v *v)
{
	if (ft_strncmp(v->cmd.filename, "pwd", 3) == 0 && ft_strlen(v->cmd.filename) == 3)
		get_pwd(v);
	else if (ft_strncmp(v->cmd.filename, "cd", 2) == 0 && ft_strlen(v->cmd.filename) == 2)
		get_cd(v);
	else if (ft_strncmp(v->cmd.filename, "echo", 4) == 0 && ft_strlen(v->cmd.filename) == 4)
		get_echo(v);
	else if (ft_strncmp(v->cmd.filename, "export", 6) == 0 && ft_strlen(v->cmd.filename) == 6)
		export_var(v);
	else if (ft_strncmp(v->cmd.filename, "unset", 5) == 0 && ft_strlen(v->cmd.filename) == 5)
		exc_var(v);
	else if (ft_strncmp(v->cmd.filename, "env", 3) == 0 && ft_strlen(v->cmd.filename) == 6)
		get_env(v);
	else if (ft_strncmp(v->cmd.filename, "exit", 4) == 0 && ft_strlen(v->cmd.filename) == 4)
		exit_msh(v);
	else
	{
		if (v->ret_last == 0)
			v->cmd.ret_status = fork_process(v);
	}
}

char	**alocate_new(t_v *v)
{
	int		i;
	char	**new;

	i = 0;
	while (v->env[i])
		i++;
	new = (char **)safe_malloc((i + 1) * sizeof(char *));
	return (new);
}

void	exc_var(t_v *v)
{
	int		i;
	int		k;
	char	**new;
	char	**aux;
	char	*var;

	if (v->cmd.cmd_args[1] != 0)
	{
		var = get_var(v);
		new = alocate_new(v);
		i = 0;
		k = 0;
		while (v->env[i] != 0)
		{
			if (ft_strncmp(v->env[i], var, ft_strlen(var)) != 0)
				new[k++] = ft_strdup(v->env[i]);
			i++;
		}
		new[k] = NULL;
		aux = v->env;
		v->env = new;
		u_free_array_bi(aux);
		free(var);
		set_return_status(v, EXIT_SUCCESS); // Failure se variavel readonly
	}
}

int	exec_com(t_v *v)
{
	int		i;
	char	*command;
	char	*aux;
	int		r;

	r = -1;
	i = 0;
	while (v->path[i] != NULL)
	{
		aux = ft_strdup(v->path[i]);
		command = ft_strjoin(aux, "/");
		free(aux);
		aux = command;
		command = ft_strjoin(aux, v->cmd.cmd_args[0]);
		r = execve(command, &v->cmd.cmd_args[0], v->env);
		free(aux);
		free(command);
		i++;
	}
	return (r);
}
