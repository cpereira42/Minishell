/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 19:28:50 by cpereira          #+#    #+#             */
/*   Updated: 2020/02/19 00:43:53 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

int		get_next_line(int fd, char **line);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strpos(const char *palheiro, char agulha);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *source);
size_t	ft_strlen(const char *frase);

#endif
