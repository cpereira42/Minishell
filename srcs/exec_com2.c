/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 00:45:53 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 18:17:02 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_com2(t_v *v)
{
	int		i;
	char	*command;
	char	*aux;
	int		r;

	//caminho absoluto
		// se existe executa
	if (is_abs_path(v->cmd.cmd_args[0]))
	{
		r = execve(v->cmd.filename, &v->cmd.cmd_args[0], v->env);
		return (r);
	}
	else //sem caminho
	{
		r = execve(v->cmd.filename, &v->cmd.cmd_args[0], v->env);
		//se existe executa
		if (r > 0)
			return (r);
		else // se nao existe
		{
			//se nao tem path: erro
			if (v->path[0] == NULL)
				return (-1);
			else
			//se tem path busca no path
			{
				r = -1;
				i = 0;

				if (v->cmd.cmd_args[1] != NULL )
					if (v->cmd.cmd_args[1][0] == '~' && v->cmd.cmd_args[1][1] != '~')
						v->cmd.cmd_args[1] = (ft_strjoin(loc_var("HOME",v),&v->cmd.cmd_args[1][1]));

					//		printf("cmd_args[0]: |%s|\n", v->cmd.cmd_args[0]);
					//		printf("cmd_args[1]: |%s|\n", v->cmd.cmd_args[1]);

				//v->cmd.cmd_args[0] = get_last_path(v->cmd.cmd_args[0]);
				v->cmd.cmd_args[0] = get_last_path2(v->cmd.cmd_args[0]);

				//		printf("cmd_args[0]: |%s|\n", v->cmd.cmd_args[0]);
				//		printf("cmd_args[1]: |%s|\n", v->cmd.cmd_args[1]);

				while (v->path[i] != NULL)
				{
					//printf("%d , %s -- %s\t",i,v->path[i],v->cmd.cmd_args[0]);
					aux = ft_strdup(v->path[i]);
					command = ft_strjoin(aux, "/");
					free(aux);
					aux = command;
					command = ft_strjoin(aux, v->cmd.cmd_args[0]);
//						printf("command: |%s|\n", command);
//						printf("cmd_args[0]: |%s|\n", v->cmd.cmd_args[0]);
//						printf("cmd_args[1]: |%s|\n", v->cmd.cmd_args[1]);
					r = execve(command, &v->cmd.cmd_args[0], v->env);
						//printf("r: %d\n", r);
					free(aux);
					free(command);
					i++;
				}
				return (r);
			}
		}
	}
}



/*
ls	ok
/bin/ls	ok
../../ls	ok
xxx/ls	ok

/bin/ls -la | /bin/grep mini	ok
../../bin/ls -la | ../../bin/grep mini	ok


unset:
/bin/ls	segv
../../ls	ok
xxx/ls		ok

/bin/ls -la | /bin/grep mini  ok
../../bin/ls -la | ../../bin/grep mini	ok


*/
