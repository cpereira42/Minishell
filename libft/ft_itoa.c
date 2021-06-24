/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:46:32 by pcunha            #+#    #+#             */
/*   Updated: 2021/06/23 19:09:08 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long long int n)
{
	int				i;
	long long int	a;

	a = n;
	i = 1;
	while (a / 10 != 0)
	{
		a = a / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long long int n)
{
	int						i;
	char					*c;
	int						s;
	long long unsigned int	nn;

	nn = (long long unsigned int)n;
	if (n < 0)
		nn = (-1) * (long long unsigned int)n;
	i = ft_count(nn);
	s = 0;
	if (n < 0)
		s = 1;
	c = (char *)malloc(i + 1 + s);
	if (c == NULL)
		return (NULL);
	c[i + s] = 0;
	while (i > 0)
	{
		c[i + s - 1] = (nn % 10) + '0';
		nn = nn / 10;
		i--;
	}
	if (s == 1)
		c[0] = '-';
	return (c);
}
