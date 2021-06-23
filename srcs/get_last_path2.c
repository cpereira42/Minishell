/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_path2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 00:15:46 by user42            #+#    #+#             */
/*   Updated: 2021/06/22 17:48:40 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_last_path2(char *str)
{
	char	**split_str;
	int		i;

	split_str = ft_split3(str, '/');
	i = 0;
	while (split_str[i])
		i++;
	if (i > 0)
		i--;
	free(str);
	str = ft_strdup(split_str[i]);
	u_free_array_bi(split_str);
	return (str);
}
