/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:44:49 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/22 16:52:23 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cd (t_v *v)
{
	char	*ptr;
	char	*aux;
	int		resp;

	update_env_var(v, "OLDPWD");
	if (v->cmd.cmd_args[1] == NULL)
		resp = chdir("..");
	else if (v->cmd.cmd_args[1][0] == '~')
		resp = chdir(ft_strjoin(loc_var("HOME", v), &v->cmd.cmd_args[1][1]));
	else
		resp = chdir(v->cmd.cmd_args[1]);
	if (resp != 0)
	{
		aux = ft_strdup("cd : no such file or directory: ");
		ptr = ft_strjoin(aux, v->cmd.cmd_args[1]);
		resp = 1;
		printf("%s\n", ptr);
		free(aux);
	}
	else
		ptr = ft_strdup("");
	update_env_var(v, "PWD");
	create_prompt(v);
	check_n_free(ptr);
	set_return_status(v, resp);
}

static void	get_echo_cont(t_v *v, int flag)
{
	if (flag)
		ft_putchar('%');
	ft_putchar('\n');
	set_return_status(v, EXIT_SUCCESS);
}

void	get_echo(t_v *v, int i, int flag, int cont)
{
	int	k;

	if (v->cmd.cmd_args[1] != NULL)
	{
		while (v->cmd.cmd_args[i] != 0)
		{
			k = 0;
			if (i > 1 && v->cmd.cmd_args[i][k] != 0 && cont == 1)
				ft_putchar(' ');
			while (v->cmd.cmd_args[i][k] != 0)
			{
				if (v->cmd.cmd_args[i][0] == '-'
					&& v->cmd.cmd_args[i][1] == 'n' && cont == 0)
					flag = 1;
				else
				{
					ft_putchar(v->cmd.cmd_args[i][k]);
					cont = 1;
				}
				k++;
			}
			i++;
		}
		get_echo_cont(v, flag);
	}
}

char	*get_var(t_v *v)
{
	char	*var;
	int		i;

	if (v->cmd.cmd_args[1] != 0)
	{
		var = ft_strdup(v->cmd.cmd_args[1]);
		i = 0;
		while (var[i] != 0 && var[i] != '=')
			i++;
		var[i] = 0;
	}
	else
		var = ft_strdup("");
	return (var);
}

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
	if (buf == NULL)
		set_return_status(v, EXIT_FAILURE);
	else
		set_return_status(v, EXIT_SUCCESS);
	free(buf);
	return (v->cmd.ret_status);
}
