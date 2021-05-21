/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:26:45 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/12 05:09:27 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_split(char	**ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	return (i);
}

void	atualiza_pasta(t_v *all)
{
	int i;
	if ( all->savein == 99)
		i = 5;
	/*all->size = pathconf(".", _PC_PATH_MAX);
	all->buf = (char *)safe_malloc((size_t)all->size);
	all->local = getcwd(all->buf, (size_t)all->size);
	all->auxiliar_vet = ft_split(all->local,'/');
	i = count_split(all->auxiliar_vet) - 1;
	all->pasta_atual = all->auxiliar_vet[i];
	all->cabecalho = ft_strjoin(all->pasta_atual, " ");
	all->cabecalho = ft_strjoin(all->cabecalho, all->nome_user);
	all->cabecalho = ft_strjoin(all->cabecalho, "$ ");
	all->path = ft_split(loc_var(all->var_ambiente,"PATH",all),':');
	//pipe(all->pp);*/
	//all->path = loc_var(all->var_ambiente,"PATH",all);
}

void	reseta_flags(t_v *all)
{

	//all->ret2 = ft_strdup("");
	//all->ret_split = ft_split(all->ret2,' ');
	//import_ambiente(env,all);
	//all->posic_pipe = 1;

	//all->var_ambiente = get_export(env,all->ret_split);

	//all->nome_user = loc_var(all->var_ambiente,"LOGNAME",all);

	//atualiza_pasta(all);

	//all->l = 0;
	all->qtd_hist = 0;
	all->savein = dup(STDIN_FILENO);
	all->saveout = dup(STDOUT_FILENO);
	all->in_fd = STDIN_FILENO;
	all->posic_string = 0;
	//printf("retorno = %s\n", loc_var(all->var_ambiente,"cezar"));


}

void add_hist(t_v *all, char *ret)
{
	all->posic_hist = all->qtd_hist;
	all->posic_string = 0;
	all->flag_exit = 0;
	all->hist[all->qtd_hist] = safe_malloc((2048 + 1) * sizeof(char*));
	ft_memcpy(all->hist[all->qtd_hist],ret,ft_strlen(ret));
	all->hist[all->qtd_hist][ft_strlen(ret)]= '\0';
	all->posic_hist = all->qtd_hist;
	all->qtd_hist++;
}
