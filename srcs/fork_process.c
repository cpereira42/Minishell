/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 00:08:16 by user42            #+#    #+#             */
/*   Updated: 2021/06/22 22:04:04 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_process(t_v *v)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	signal(SIGINT, sighandlerchild);
	signal(SIGQUIT, sighandlerchild);
	tcsetattr(0, TCSANOW, &v->intterm);
	if (pid < 0)
	{
		printf("erro no fork\n");
		set_return_status(v, EXIT_FAILURE);
		return (127);
	}
	else if (pid == 0)
	{
		set_return_status(v, EXIT_SUCCESS);
		status = exec_com2(v);
		v->pidc = getpid();
		v->cmd.ret_status = status;
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}
