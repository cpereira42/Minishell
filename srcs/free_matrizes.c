/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrizes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 01:32:49 by user42            #+#    #+#             */
/*   Updated: 2021/05/26 15:35:19 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_matrizes(char **s)
{
	int	i;
	int	n;

	i = 0;
	n = ft_conta_linhas(s);
	while (i < n)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}
