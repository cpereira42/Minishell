/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:22:52 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 17:35:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == 18)
		printf("Ctrl = C\n");
	if (signum == 2)
		exit (0);
	if (signum == 3)
	{
		printf("Ctrl = a\n");
		exit (0);
	}
	printf("Caught signal %d, coming out...\n", signum);
}
