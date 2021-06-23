/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcunha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 18:38:27 by pcunha            #+#    #+#             */
/*   Updated: 2021/05/10 18:17:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	base_size(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

int	check_plus_minus(char *base)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			error = 1;
		i++;
	}
	return (error);
}

int	check_repeated(char *base)
{
	int	i;
	int	j;
	int	error;

	error = 0;
	i = 0;
	while (base[i] != '\0')
	{
		j = 0;
		while (base[j] != '\0')
		{
			if (base[j] == base[i] && i != j)
				error = 1;
			j++;
		}
		i++;
	}
	return (error);
}

int	check_errors(char *base)
{
	int	error;
	int	n_base;

	error = 0;
	n_base = base_size(base);
	if (n_base <= 1)
		error = 1;
	if (check_plus_minus(base) == 1)
		error = 1;
	if (check_repeated(base) == 1)
		error = 1;
	return (error);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	n_base;
	char			d;
	unsigned int	n;

	n = nbr;
	if (check_errors(base) == 0)
	{
		n_base = base_size(base);
		if (nbr < 0)
		{
			write(1, "-", 1);
			n = -nbr;
		}
		if (n > n_base - 1)
		{
			ft_putnbr_base(n / n_base, base);
			ft_putnbr_base(n % n_base, base);
		}
		else
		{
			d = base[n];
			write(1, &d, 1);
		}
	}
}
