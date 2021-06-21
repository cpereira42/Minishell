/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 00:33:21 by user42            #+#    #+#             */
/*   Updated: 2021/06/11 01:00:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    exec_cmd3(char *path, char **args, t_v *v)
{
    pid_t    pid;
    int        ret;

    ret = 0;
    pid = fork();
    if (pid == 0)
    {
        ret = execve(path, args, v->env);
        exit(ret);
    }
    else if (pid < 0)
    {
//        free(path);
        ft_putendl_fd("minishell: failed to create a new process.", 1);
    }
    waitpid(pid, &ret, 0);
//    if (path)
//        free(path);
    return (ret);
}
