/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:22:52 by user42            #+#    #+#             */
/*   Updated: 2021/05/24 16:25:59 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	pid_t	pidf;

	if (signum == 18)
	{
		pidf = getpid();
		kill(pidf, SIGKILL);
	}
	if (signum == 2)
	{
		printf("Saindo = \n");
		exit (0);
	}

	if (signum == 3)
	{
		printf("Ctrl = \n");
		exit (0);
	}
	printf("Caught signal %d, coming out...\n", signum);
}
