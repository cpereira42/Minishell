/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:47 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 17:03:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

int		ft_conta_palavras2(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*malloc_palavra2(char const *s, char c)
{
	char	*palavra;
	int		i;

	i = 0;
	while (s[i] && !(s[i] == c))
		i++;
	palavra = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && !(s[i] == c))
	{
		palavra[i] = s[i];
		i++;
	}
	palavra[i] = '\0';
	return (palavra);
}

int		ft_count_words(char const *s, char c)
{
	int i;
	int	count;
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
	while (i < ft_count_words(s, c))
	//while (i < ft_conta_palavras2(s, c))
	{
		out[i] = (char*)malloc(MIL);
		ft_bzero(out[i], MIL);
		i++;
	}
	return (out);
}

char	**ft_split2(char const *s, char c)
{
	char					**out;
	int						i;
	int						j;
	int						k;
	t_estado_parse_s		estado;

	i = 0;
	j = 0;
	k = 0;
	estado = NORMAL;
	if (s == NULL)
		return (NULL);
	out = init_array(s, c);
	if (out == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		if ((s[i] == c && estado == NORMAL) || s[i] == 0)
		{
			out[j][k] = 0;
			j++;
			k = 0;
		}
		else
		{
			out[j][k] = s[i];
			k++;
		}
		i++;
		parse_sq(s[i], &i, &estado);
		parse_dq(s[i], &i, &estado);
	}
	j++;
	out[j] = NULL;
	dprintf(1, "j: %d\n", j);
	//printf("debug :\nj: %d\n", j);
	//u_print_array_bi(out);
	//printf("---------\n");
	return (out);
}
