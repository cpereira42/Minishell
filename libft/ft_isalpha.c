/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcunha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:58:45 by pcunha            #+#    #+#             */
/*   Updated: 2021/05/10 18:01:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int c)
{
	int	a;

	a = 0;
	if (c >= 97 && c <= 122)
		a = 1;
	return (a);
}

static int	ft_isupper(int c)
{
	int	a;

	a = 0;
	if (c >= 65 && c <= 90)
		a = 1;
	return (a);
}

int	ft_isalpha(int c)
{
	int	a;

	a = 0;
	if (ft_islower(c) || ft_isupper(c))
		a = 1;
	return (a);
}
