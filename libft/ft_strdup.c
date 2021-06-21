/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:25:43 by pcunha            #+#    #+#             */
/*   Updated: 2021/05/22 12:51:46 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*d;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	d = (char *)malloc(len + 1);
	if (d == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i < len + 1)
	{
		d[i] = s1[i];
		i++;
	}
	return (d);
}
