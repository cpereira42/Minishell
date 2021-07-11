/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:40:43 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 09:32:51 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_v *v, int fd_temp)
{
	char	*line;

	tcsetattr(0, TCSAFLUSH, &v->old);
	line = readline("heredoc> ");
	if (ft_strncmp(line, v->eof, ft_strlen(v->eof)))
	{
		ft_putstr_fd(line, fd_temp);
		ft_putstr_fd("\n", fd_temp);
	}
	while (ft_strncmp(line, v->eof, ft_strlen(v->eof)))
	{
		free(line);
		line = readline("heredoc> ");
		if (ft_strncmp(line, v->eof, ft_strlen(v->eof)))
		{
			ft_putstr_fd(line, fd_temp);
			ft_putstr_fd("\n", fd_temp);
		}
	}
	free(line);
}

void	rm_file(void)
{
	unlink ("./zzzz");
}
