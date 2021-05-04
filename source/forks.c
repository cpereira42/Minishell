/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:18:13 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/03 16:28:09 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

int teste_fork(t_all *all)
{
	int j;
	int in_fd;
	int out_fd;
	int	fd[2];
	int status;
	char **ret_split;
	if (all->pp[1] != '\0')
	{
		j = 1;
		//ft_putstr_fd("cezar",all->pp[1]);
		close(all->pp[1]);
		in_fd = all->pp[0];
	}
	else
		j = 0;

	while (j < all->qtd_pipe)
	{
		if(pipe(fd) < 0)
		{
			printf("erro pipe");
			return(127);
		}
		out_fd = fd[1];
		ret_split = ft_split(all->pipe_split[j],' ');
		status = execute_process2(all, in_fd, out_fd, ret_split);
		close(out_fd);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		j++;
	}

	ret_split = ft_split(all->pipe_split[all->qtd_pipe],' ');
	status = execute_process2(all, in_fd, STDOUT_FILENO, ret_split);
	close(all->pp[1]);
	close(all->pp[0]);
	return(status);
}
int		execute_process2(t_all *all, int in, int out, char **args)
{
	pid_t pid;
	int status;

	status = 0;

	if ((pid = fork()) < 0)
	{
		printf("erro no fork\n");
		return (127);
	}
	else if (pid == 0)
	{
		file_descriptor_handler(in,out);
		return(exec_com(all, args));
	}
	else
	{
		waitpid(pid,&status,0);
		//close(all->pp[1]);
	}

	return(0);
}

int exec_com(t_all *all, char **args)
{
	int i;
	char *comando;
	int r;

	r = -1;
	i = 0;

	args[1] = ft_strtrim(args[1],"\"");

	while (all->path[i] != NULL  )
	{
		comando = ft_strdup(all->path[i]);
		comando = ft_strjoin(comando,"/");
		comando = ft_strjoin(comando,args[0]);
		r = execve(comando, &args[0] ,all->var_ambiente);
		i++;
	}
	return (r);
}
int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}
