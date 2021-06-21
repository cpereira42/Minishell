/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcunha <pcunha@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 12:53:27 by pcunha            #+#    #+#             */
/*   Updated: 2021/05/10 18:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	base_size(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

static long int	ft_count(long long unsigned int n, long unsigned int nb)
{
	long long unsigned int	i;
	long long unsigned int	a;

	a = n;
	i = 1;
	while (a / nb != 0)
	{
		a = a / nb;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(long long int n, char *base)
{
	int						i;
	char					*c;
	int						s;
	long long unsigned int	nn;
	long long unsigned int	nb;

	nn = (long long unsigned int)n;
	nb = (long long unsigned int)base_size(base);
	i = ft_count(nn, nb);
	s = 0;
	c = (char *)malloc(i + 1 + s);
	if (c == NULL)
		return (NULL);
	c[i + s] = 0;
	while (i > 0)
	{
		c[i + s - 1] = base[nn % nb];
		nn = nn / nb;
		i--;
	}
	if (s == 1)
		c[0] = '-';
	return (c);
}
