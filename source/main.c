/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:20:18 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/05 21:09:56 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>

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

void ls (void)
{
	DIR *folder;
	struct dirent *entry;
	struct stat sfile;
	int files = 0;

	folder = opendir(".");
	if(folder == NULL)
		perror("Unable to read directory");
	while( (entry=readdir(folder)) )
	{
		files++;
		if(entry->d_name[0]!= '.')
		{


			if(lstat(entry->d_name,&sfile)==-1)
    			printf("Error Occurred\n");
			else
			{
				printf((sfile.st_mode & S_IRUSR)? "r":"-");
				printf((sfile.st_mode & S_IWUSR)? "w":"-");
				printf((sfile.st_mode & S_IXUSR)? "x":"-");
				printf((sfile.st_mode & S_IRGRP)? "r":"-");
				printf((sfile.st_mode & S_IWGRP)? "w":"-");
				printf((sfile.st_mode & S_IXGRP)? "x":"-");
				printf((sfile.st_mode & S_IROTH)? "r":"-");
				printf((sfile.st_mode & S_IWOTH)? "w":"-");
				printf((sfile.st_mode & S_IXOTH)? "x":"-");
			}
			//printf(" %hu   ",sfile.st_nlink);
			printf("   %s \n",entry->d_name);
		}
	}
	closedir(folder);
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
	static
	int ret;
	ret = get_next_line(0, &buff);
	hist[qtd_hist] = malloc((1024 + 1) * sizeof(char*));
	hist[qtd_hist] = buff;
	qtd_hist++;
	ret = 2;
	if (ret == 1)
		ret = 2;
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

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}

int my_termprint(int c){
	return write(1, &c, 1);
}

char *term_get_cap(char* cap){

    char* area = malloc(2048);
    char* str;

    //return 0;
    str = tgetstr(cap ,(char**)(&area));
    /*if(!str){
        my_str("bad call on");
        my_str(cap);

    }*/
    //return 0;
    return str;

}

int    teste()
{
    char buf[1024];
    char *str;

	printf("entrou\n");
    tgetent(buf, getenv("TERM"));
    str = tgetstr("cl", NULL);
	//str = tgetstr("up", NULL);
    fputs(str, stdout);
	//printf("t=%s\n",str);
	//printf("tchau\n");
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char *ret2;
	int l;
	char **ret_split;
	char **var_ambiente;
	char *pasta_atual;


    char ret[2048];
    tgetent(ret, getenv("TERM"));

	struct termios term;
	tcgetattr(0,&term);

	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
	tcsetattr(0,TCSANOW,&term);


	qtd_hist = 0;

	//teste();
	printf("Hello World!\n");
	printf ("env = %s av = %s ac = %d\n", env[1],av[0],ac);
	printf ("Bem vindo ao MINISHEL2L");

	ret2  = ft_strdup("");
	ret_split = ft_split(ret,' ');
	var_ambiente = get_export(env,ret_split);
	pasta_atual = ft_strdup("teste");


	write (1,"teste",5);
	tputs(tigetstr("ce"),1,my_termprint); // ed



	tputs(save_cursor,1,my_termprint);
	int posic_hist;
	while (1)
	{

		l = read (0,ret,100);
		if (!ft_strncmp("\e[A",ret,3)) // cima
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint); //kL
			ret2 = ft_strdup(hist[posic_hist]);
			write (1,ret2,ft_strlen(ret2));
			if (posic_hist <= 0)
				posic_hist = 0;
			else
				posic_hist --;
				ret[0] = 0;
		}
		else if (!ft_strncmp("\e[B",ret,3)) // baixo
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint);
			ret2 = ft_strdup(hist[posic_hist]);
			write (1,ret2,ft_strlen(ret2));

			if (posic_hist >= qtd_hist - 1)
				posic_hist = qtd_hist - 1;
			else
				posic_hist ++;
		}
		else if (!ft_strncmp("\e[C",ret,3))
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint); // ed
			//ft_bzero(ret,2048);
			//ret2 = ft_strdup("");
			//write (1,"dir\n",3);
		}
		else if (!ft_strncmp("\e[D",ret,3))
		{
			//tputs(restore_cursor,1,my_termprint);
			//tputs(tigetstr("ed"),1,my_termprint);
			tputs(clear_screen,1,my_termprint);
			//ft_bzero(ret,2048);
			//ret2 = ft_strdup("");
			//write (1,"esq\n",3);
		}
		else if (!ft_strncmp("\n",ret,1))
		{
			posic_hist = qtd_hist;
			execulta_comando (ret2,var_ambiente);
			tputs(save_cursor,1,my_termprint);
			ft_bzero(ret2,2048);
			ft_bzero(ret,2048);
		}
		else if (ret[0] == 127)
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint);
			//tputs(tigetstr("kD"),1,my_termprint);
			ret2[ft_strlen(ret2)-1] = 0;
			write (1,ret2,ft_strlen(ret2));
		}
		else
		{
			ret2 = ft_strjoin(ret2,ret);
			write (1,ret,l);
		}


	}
	return (0);
}

void execulta_comando (char *ret, char **var_ambiente)
{
	char **comandos;
	int i;
	char **ret_split;
	char *pasta_atual;

	hist[qtd_hist] = malloc((1024 + 1) * sizeof(char*));
	ft_memcpy(hist[qtd_hist],ret,ft_strlen(ret));
	qtd_hist++;

	printf ("frase = %s\n",ret);
	pasta_atual = ft_strdup("teste");
	//ret = ft_strtrim(ret, " ");
		comandos = ft_split(ret,';');
		i = 0;
		while (comandos[i] != NULL || i == 0 )
		{
			ret_split = ft_split(comandos[i],' ');
			if (ft_strncmp(ret_split[0],"pwd",3) == 0 && ft_strlen(ret_split[0]) == 3)
				printf("%s\n",get_pwd(ret_split));
			else if(ft_strncmp(ret_split[0],"ls",2) == 0 && ft_strlen(ret_split[0]) == 2)
				ls();
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
			else if (ft_strncmp(ret_split[0],"clear",5) == 0 && ft_strlen(ret_split[0]) == 5)
				tputs(clear_screen,1,my_termprint);
			else if(ft_strncmp(ret_split[0],"exit",4) == 0 && ft_strlen(ret_split[0]) == 4)
			{
				printf("Saindo\n");
			}
			else
			{
				ft_bzero(ret,2048);
				//ret = ft_strdup("");
				printf ("Command not found\n");
			}
			i++;
		}
}
