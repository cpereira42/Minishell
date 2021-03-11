/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:20:18 by cpereira          #+#    #+#             */
/*   Updated: 2021/03/10 16:59:51 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

#include <stdio.h>

char	*hist[50];
int		qtd_hist;

char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strpos(const char *palheiro, char agulha);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *source);

char *get_cd (char **ret)
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
	return (ptr);
}

char *get_echo (char **ret)
{
	char *ptr;
	int i;
	int flag;
	int count;

	i = 1;
	flag = 0;
	count = 0;
	ptr = ft_strdup("");
	while (ret[i] != NULL)
	{
		if (ft_strncmp(ret[i], "-n", 2) == 0 && count == 0)
			flag = 1;
		else
		{
			if (i-flag != 1 && count != 0 )
				ptr = ft_strjoin (ptr, " ");
			ptr = ft_strjoin (ptr,ret[i]);
			count ++;
		}
		i++;
	}
	if (flag == 1)
		ptr = ft_strjoin (ptr,"%");
	return (ptr);
}

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

char **get_export (char **ret, char **entrada)
{
	int i;
	int flag;
	int count;
	char **saida;
	int qtd_args;

	flag = 0;
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
			flag = 1;
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

char *get_pwd (char **ret)
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
	return (ptr);
}

char *get_line(void)
{
	char *buff;
	int ret;
	ret = get_next_line(0, &buff);
	hist[qtd_hist] = malloc((1024 + 1) * sizeof(char*));
	hist[qtd_hist] = buff;
	qtd_hist++;
	return (buff);
}

void	lista_hist(void)
{
	int i = 0;
	printf ("\nhistorico comandos \n");
	while (i<qtd_hist)
	{
		printf("%s\n",hist[i]);
		i++;
	}
}

int		main(int ac, char **av, char **env)
{
	char *ret;
	char **comandos;
	char **ret_split;
	char **var_ambiente;
	char *pasta_atual;
	int i;

	qtd_hist = 0;
	i = 0;

	printf ("env = %s av = %s ac = %d\n", env[1],av[0],ac);
	printf ("Bem vindo ao MINISHELL\n");

	ret  = ft_strdup("");
	ret_split = ft_split(ret,' ');
	var_ambiente = get_export(env,ret_split);
	pasta_atual = ft_strdup("teste");

	//ler_export(var_ambiente);

	while (1)
	{

		i = 0;
		ret = get_line();
		ret = ft_strtrim(ret, " ");
		comandos = ft_split(ret,';');
		while (comandos[i] != NULL || i == 0 )
		{
			ret_split = ft_split(comandos[i],' ');
			if (ft_strncmp(ret_split[0],"pwd",3) == 0 && ft_strlen(ret_split[0]) == 3)
				printf("%s\n",get_pwd(ret_split));
			else if(ft_strncmp(ret_split[0],"echo",4) == 0 && ft_strlen(ret_split[0]) == 4)
				printf("%s\n",get_echo(ret_split));
			else if(ft_strncmp(ret_split[0],"cd",2) == 0 && ft_strlen(ret_split[0]) == 2)
				printf("%s\n",get_cd(ret_split));
			else if(ft_strncmp(ret_split[0],"unset",5) == 0 && ft_strlen(ret_split[0]) == 5)
				var_ambiente = exc_var(var_ambiente,ret_split);
			else if(ft_strncmp(ret_split[0],"export",6) == 0 && ft_strlen(ret_split[0]) == 6)
				var_ambiente = get_export(var_ambiente,ret_split);
			else if(ft_strncmp(ret_split[0],"env",3) == 0 && ft_strlen(ret_split[0]) == 3)
				ler_export(var_ambiente);
			else if(ft_strncmp(ret_split[0],"exit",4) == 0 && ft_strlen(ret_split[0]) == 4)
			{
				printf("Saindo\n");
				return(0);
			}
			else
				printf ("Command not found\n");
			i++;
			printf("%s\n",pasta_atual); // alterar para comando write_fd
		}
	}
	return (0);
}
