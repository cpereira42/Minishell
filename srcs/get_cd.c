/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:15:36 by user42            #+#    #+#             */
/*   Updated: 2021/05/22 10:28:28 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	atualiza_pasta(t_v *v)
{
	int i;

	all->buf = (char *)safe_malloc((size_t)all->size);
	all->local = getcwd(all->buf, (size_t)all->size);
	all->auxiliar_vet = ft_split(all->local,'/');
	i = count_split(all->auxiliar_vet) - 1;
	all->pasta_atual = all->auxiliar_vet[i];
	all->cabecalho = ft_strjoin(all->pasta_atual, " ");
	all->cabecalho = ft_strjoin(all->cabecalho, all->nome_user);
	all->cabecalho = ft_strjoin(all->cabecalho, "$ ");
	all->path = ft_split(loc_var(all->var_ambiente,"PATH",all),':');
	pipe(all->pp);
	//all->path = loc_var(all->var_ambiente,"PATH",all);
}
*/

void	get_cd (t_v *v)
{
	char *ptr;
	char *aux;
	int resp;

	update_env_var(v, "OLDPWD");
	if (v->cmd.cmd_args[1] == NULL)
		resp = chdir("..");
	else
		resp = chdir(v->cmd.cmd_args[1]);

	if (resp != 0)
	{
		aux = ft_strdup("cd : no such file or directory: ");
		ptr = ft_strjoin(aux,v->cmd.cmd_args[1]);
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
