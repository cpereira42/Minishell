/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:26:45 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/07 19:27:44 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

int		count_split(char	**ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	return (i);
}

void	atualiza_pasta(t_all *all)
{
	int i;

	all->size = pathconf(".", _PC_PATH_MAX);
	all->buf = (char *)malloc((size_t)all->size);
	all->local = getcwd(all->buf, (size_t)all->size);
	all->auxiliar_vet = ft_split(all->local,'/');
	i = count_split(all->auxiliar_vet) - 1;
	all->pasta_atual = all->auxiliar_vet[i];
	all->cabecalho = ft_strjoin(all->pasta_atual, " ");
	all->cabecalho = ft_strjoin(all->cabecalho, all->nome_user);
	all->cabecalho = ft_strjoin(all->cabecalho, "$ ");

}

void	reseta_flags(t_all *all, char **env)
{

	all->ret2 = ft_strdup("");
	all->ret_split = ft_split(all->ret2,' ');
	all->var_ambiente = get_export(env,all->ret_split);
	all->nome_user = loc_var(all->var_ambiente,"LOGNAME");
	atualiza_pasta(all);
	all->qtd_hist = 0;
	all->l = 0;

	//printf("retorno = %s\n", loc_var(all->var_ambiente,"cezar"));


}
