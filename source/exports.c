/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:28:51 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/10 15:57:40 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

void exc_var (char **entrada, t_all *all)
{
	int i;
	//char *var;
	char **termo;
	int posicao;

	i = 0;
	while (entrada[i] != NULL)
	{
		posicao = ft_strpos(entrada[i],'=');
		if (posicao == 0)
			loc_var(all->var_ambiente,entrada[i],all);
		else
		{
			termo = ft_split(entrada[i],'=');
			loc_var(all->var_ambiente,termo[0],all);
		}
		if (all->var_posic != -1) // exclui variavel e atualiza variavel de ambiente
			excluir(all);
		i++;
	}
	free (termo);

}

void excluir(t_all *all)
{
	char **saida;
	int i;
	int j;

	i = 0;
	j = 0;
	saida = malloc((all->tam_ambiente + 1) * sizeof(char*));
	while (all->var_ambiente[i] != NULL)
	{
		if (i != all->var_posic)
		{
			saida[j] = ft_strdup(all->var_ambiente[i]);
			j++;
		}

		i++;
	}
	saida[j] = "\0";
	import_ambiente(saida,all);
}

char *loc_var (char **ret, char *entrada, t_all *all)
{
	int i;
	size_t tam;

	all->var_posic = -1;
	i = 0;
	tam = ft_strlen(entrada);
	while (ret[i] != NULL)
	{
		if (ft_strncmp(entrada,ret[i],tam) == 0 && ret[i][tam] == '=' )
		{
			all->var_posic = i;
			return(&ret[i][tam+1]);
		}
		i++;
	}
	return ("");
}

void	import_ambiente(char **ret, t_all *all)
{
	int		i;
	int 	count;

	count = 0;
	i = 0;
	//if (all->var_ambiente)

	while (ret[i] != NULL)
		i++;
	all->tam_ambiente = i;
	all->var_ambiente = malloc((i + 1) * sizeof(char*));
	i = 0;
	while (ret[i] != NULL)
	{
		if (ft_strncmp(ret[i], "-", 1) == 0 && count == 0)
			;//flag = 1;
		else
		{
			all->var_ambiente[i] = ft_strdup(ret[i]);
			count ++;
		}
		i++;
	}
	all->var_ambiente[i] = "\0";
	all->tam_ambiente = i - 1;

}

void export_var (t_all *all, char **entrada)
{
	int i;
	int count;
	char **saida;
	int qtd_args;

	count = 0;
	i = 0;
	qtd_args = 0;

	exc_var(&entrada[1],all);
	while (entrada[qtd_args]!= NULL)
		qtd_args++;

	saida = malloc((all->tam_ambiente + qtd_args + 1) * sizeof(char*));
	i = 0;
	while (all->var_ambiente[i] != NULL)
	{
		if (ft_strncmp(all->var_ambiente[i], "-", 1) == 0 && count == 0)
			;//flag = 1;
		else
		{
			saida[i] = all->var_ambiente[i];
			count ++;
		}
		i++;
	}
	qtd_args = 0;
	while (entrada[qtd_args] != NULL)
	{
		saida[i + qtd_args] = entrada[qtd_args + 1];
		qtd_args++;
	}
	saida[i + qtd_args] = "\0";
	import_ambiente(saida,all);
}

void ler_export(char **ret)
{
	int i;

	i = 0;
	while (ret[i] != NULL)
	{
		printf("(%d)%s\n",i,ret[i]);
		i++;
	}
}

void	free_array(void **array)
{
	unsigned	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
