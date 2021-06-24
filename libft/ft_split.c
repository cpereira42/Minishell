/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:10:07 by pcunha            #+#    #+#             */
/*   Updated: 2021/06/23 19:08:29 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_count_words(char const *s, char c)
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

char	*malloc_word(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !(s[i] == c))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && !(s[i] == c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i;

	if (s == NULL)
		return (NULL);
	out = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			out[i] = malloc_word(s, c);
			i++;
			while (*s && !(*s == c))
				s++;
		}
	}
	out[i] = NULL;
	return (out);
}
