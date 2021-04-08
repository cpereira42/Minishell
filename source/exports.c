/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:28:51 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/07 18:29:58 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

char **exc_var (char **ret, char **entrada)
{
	int i;
	int j;

	char **saida;
	size_t tam;

	i = 0;
	while (ret[i] != NULL)
		i++;
	saida = malloc((i + 1) * sizeof(char*));
	i = 0;
	j = 0;
	while (entrada[i] != NULL)
	{
		tam = ft_strlen(entrada[i]);
		while (ret[j] != NULL)
		{
			if (ft_strncmp(entrada[i],ret[j],tam) == 0 && ret[j][tam] == '=' )
				ret[j][0] = '#'; // termo para excluir
				//printf("achou(%c)(%c)\n",ret[j][tam],ret[j][tam+1]);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;

	while (ret[i] != NULL)
	{
		if(ret[i][0]!='#')
		{
			saida[j] = ret[i];
			j++;
		}
		i++;
	}
	saida[i] = "\0";
	return (saida);
}


char *loc_var (char **ret, char *entrada)
{
	int i;
	size_t tam;

	i = 0;
	tam = ft_strlen(entrada);
	while (ret[i] != NULL)
	{
		if (ft_strncmp(entrada,ret[i],tam) == 0 && ret[i][tam] == '=' )
			return(&ret[i][tam+1]);
		i++;
	}
	return (0);
}

char **get_export (char **ret, char **entrada)
{
	int i;
	//int flag;
	int count;
	char **saida;
	int qtd_args;

	//flag = 0;
	count = 0;
	i = 0;
	qtd_args = 0;

	while (ret[i] != NULL)
		i++;
	while (entrada[qtd_args]!= NULL)
		qtd_args++;
	saida = malloc((i + qtd_args + 1) * sizeof(char*));
	i = 0;
	while (ret[i] != NULL)
	{
		if (ft_strncmp(ret[i], "-", 1) == 0 && count == 0)
			;//flag = 1;
		else
		{
			saida[i] = ret[i];
			count ++;
		}
		i++;
	}
	qtd_args = 0;
	while (entrada[qtd_args] != NULL)
	{
		saida[i + qtd_args] = entrada[qtd_args + 1];
		//printf("saida ----  \n%s \n ----",saida[i + qtd_args]);
		qtd_args++;
	}
	saida[i + qtd_args] = "\0";
	return (saida);
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
