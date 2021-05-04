/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:58:14 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/03 16:31:36 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include "../includes/libft.h"

char *get_cd (char **ret,t_all *all)
{
	char *ptr;
	int resp;

	if (ret[1] == NULL)
		resp = chdir("..");
	else
		resp = chdir(ret[1]);

	if (resp != 0)
	{
		ptr = ft_strdup("cd : no such file or directory: ");
		ptr = ft_strjoin(ptr,ret[1]);
	}
	else
		ptr = ft_strdup("");
	atualiza_pasta(all);
	ft_putstr_fd(ptr,1);
	return (ptr);
}

void get_echo (char **ret, t_all *all, int fd)
{
	char *ptr;
	char *termo;
	int i;
	int flag;
	int count;

	i = 1;
	flag = 0;
	count = 0;
	ptr = ft_strdup("");

	while (ret[i] != NULL)
	{
		if (ret[i][0]== '$')
			termo = loc_var(all->var_ambiente,&ret[i][1],all);
		else
			termo = ft_strdup(ret[i]);

		if (termo[0] == '"' || termo[0] == '\'' )
			termo = termo[0] == '"' ? ft_strtrim(termo,"\""): ft_strtrim(termo,"'") ;
		if (ft_strncmp(ret[i], "-n", 2) == 0 && count == 0)
			flag = 1;
		else
		{
			if (i-flag != 1 && count != 0 )
				ptr = ft_strjoin (ptr, " ");
			ptr = ft_strjoin (ptr,termo);
			count ++;
		}
		i++;
	}
	if (flag == 1)
		ptr = ft_strjoin (ptr,"%");

	if (all->qtd_pipe == 0 || all->qtd_pipe == all->posic_pipe)
		ft_putstr_fd(ptr,fd);
	else
	{
		ft_putstr_fd(ptr, all->pp[1]);
		teste_fork(all);
		all->ret_aux = ptr;
	}
}

int get_pwd (char **ret, t_all *all, int fd)
{
	long size;
	char *buf;
	char *ptr;

	if (ret[2]!= NULL && ft_strlen(*ret) == 3)
	{
		size = pathconf(".", _PC_PATH_MAX);
		buf = (char *)malloc((size_t)size);
		ptr = getcwd(buf, (size_t)size);
	}
	else
	{
		ptr = ft_strdup("pwd : too many arguments");
	}


	if (all->qtd_pipe == 0 || all->qtd_pipe == all->posic_pipe)
	{
		ft_putstr_fd(ptr,fd);
		ft_putstr_fd("\n",fd);
	}
	else
	{

		ft_putstr_fd(ptr, all->pp[1]);
		teste_fork(all);
		all->ret_aux = ptr;
	}


	//ft_putstr_fd(ptr,1);
	return (0);
}
