/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 22:19:37 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 17:39:30 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd (t_v *v)
{
	long	size;
	char	*buf;

	size = MIL;
	buf = NULL;
	if (v->cmd.cmd_args[1] == NULL)
		buf = getcwd(buf, (size_t)size);
	else
		buf = ft_strdup("pwd : too many arguments");
	printf("%s\n", buf);
	//ft_putstr_fd(buf, v->cmd.fd_out);
	//ft_putstr_fd("\n", v->cmd.fd_out);
	if (buf == NULL)
		set_return_status(v, EXIT_FAILURE);
	else
		set_return_status(v, EXIT_SUCCESS);
	free(buf);
	return (v->cmd.ret_status);
}
