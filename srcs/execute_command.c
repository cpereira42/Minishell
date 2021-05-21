/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 01:11:30 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 19:14:52 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_v *v)
{
	if (ft_strncmp(v->cmd.filename, "pwd", 3) == 0)
		get_pwd(v);
	else if (ft_strncmp(v->cmd.filename, "cd", 2) == 0)
		get_cd(v);
	else if (ft_strncmp(v->cmd.filename, "echo", 4) == 0)
		get_echo(v);
	else if (ft_strncmp(v->cmd.filename, "export", 6) == 0)
		export_var(v);
	else if (ft_strncmp(v->cmd.filename, "unset", 5) == 0)
		exc_var(v);
	else if (ft_strncmp(v->cmd.filename, "env", 3) == 0)
		get_env(v);
	else if (ft_strncmp(v->cmd.filename, "exit", 4) == 0)
		exit_msh(v);
	else
		v->cmd.ret_status = fork_process(v);
}
