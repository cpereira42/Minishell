/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 02:21:52 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 18:08:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

char **perform_splits(int n, int j, char s[])
{
	int i;
	char **out;

	out = (char **)malloc(sizeof(char*) * (j + 2));
	out[0] = ft_strdup(&s[0]);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (s[i] == 0)
		{
			j++;
			out[j] = ft_strdup(&s[i+1]);
		}
		i++;
	}
	return (out);
}

char	**ft_split3(char s[], char c)
{
	int i;
	int	j;
	char **out;
	t_estado_parse_s		estado;

	estado = NORMAL;
	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			s[i] = 0;
			j++;
		}
		i++;
		parse_sq(s[i], &i, &estado);
		parse_dq(s[i], &i, &estado);
	}
	out = perform_splits(i, j, s);
	j++;
	out[j] = NULL;
	return (out);
}
