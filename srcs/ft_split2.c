/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:47 by user42            #+#    #+#             */
/*   Updated: 2021/05/26 15:34:45 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

int	ft_count_words(char const *s, char c)
{
	int						i;
	int						count;
	t_estado_parse_s		estado;

	count = 1;
	estado = NORMAL;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c && estado == NORMAL)
			count++;
		i++;
		parse_sq(s[i], &i, &estado);
		parse_dq(s[i], &i, &estado);
	}
	return (count);
}

char	**init_array(char const *s, char c)
{
	char	**out;
	int		i;

	if (s == NULL)
		return (NULL);
	out = (char **)malloc(sizeof(char *) * (ft_conta_palavras2(s, c) + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	printf("count_words: %d\n", ft_count_words(s, c));
	{
		out[i] = (char *)malloc(MIL);
		ft_bzero(out[i], MIL);
		i++;
	}
	return (out);
}
