/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 00:08:16 by user42            #+#    #+#             */
/*   Updated: 2021/05/28 19:54:12 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_process(t_v *v)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		printf("erro no fork\n");
		set_return_status(v, EXIT_FAILURE);
		return (127);
	}
	else if (pid == 0)
	{
		set_return_status(v, EXIT_SUCCESS);
		return (exec_com(v));
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}
