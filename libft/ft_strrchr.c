/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:55:47 by cpereira          #+#    #+#             */
/*   Updated: 2020/01/28 18:22:38 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
    int i;
    
    i = ft_strlen(s);
    while (i >= 0)
    {
        if (s[i] == c)
            return ((char *)s + i);
        i--;
    }
    return (NULL);
}
