/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:20:18 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/07 19:25:30 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>

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
/*
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
}*/

void	lista_hist(t_all *all)
{
	int i = 0;
	printf ("\nhistorico comandos \n");
	while (i<all->qtd_hist)
	{
		printf("%s\n",all->hist[i]);
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

int		main(int ac, char **av, char **env)
{
	t_all all;
	int l;

	char ret[2048];
	reseta_flags(&all, env);
    tgetent(ret, getenv("TERM"));

	struct termios term;
	tcgetattr(0,&term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
	tcsetattr(0,TCSANOW,&term);

	all.ac = ac;
	all.av = av;

	//printf ("env = %s av = %s ac = %d\n", env[1],av[0],ac);

	ft_putstr_fd("Bem vindo ao MINISHELL CPEREIRA & PCUNHA\n",1);

	ft_putstr_fd(all.cabecalho,1);

	tputs(tigetstr("ce"),1,my_termprint); // ed
	tputs(save_cursor,1,my_termprint);

	while (1)
	{
		ft_bzero(ret,2048);
		l = read (0,ret,100);
		if (!ft_strncmp("\e[A",ret,3)) // cima
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint); //kL
			all.ret2 = ft_strdup(all.hist[all.posic_hist]);
			write (1,all.ret2,ft_strlen(all.ret2));
			if (all.posic_hist <= 0)
				all.posic_hist = 0;
			else
				all.posic_hist --;
				ret[0] = 0;
		}
		else if (!ft_strncmp("\e[B",ret,3)) // baixo
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint);
			all.ret2 = ft_strdup(all.hist[all.posic_hist]);
			write (1,all.ret2,ft_strlen(all.ret2));

			if (all.posic_hist >= all.qtd_hist - 1)
				all.posic_hist = all.qtd_hist - 1;
			else
				all.posic_hist ++;
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
			all.posic_hist = all.qtd_hist;
			execulta_comando (all.ret2,&all);
			tputs(save_cursor,1,my_termprint);
			ft_bzero(all.ret2,2048);
			ft_bzero(all.ret,2048);
			ft_putstr_fd(all.cabecalho,1);
		}
		else if (ret[0] == 127)
		{
			tputs(restore_cursor,1,my_termprint);
			tputs(tigetstr("ed"),1,my_termprint);
			//tputs(tigetstr("kD"),1,my_termprint);
			all.ret2[ft_strlen(all.ret2)-1] = 0;
			ft_putstr_fd(all.ret2,1);
		}
		else
		{
			all.ret2 = ft_strjoin(all.ret2,ret);
			ft_putstr_fd(ret,1);
		}
	}
	return (0);
}

void execulta_comando (char *ret, t_all *all)
{
	char **comandos;
	int i;
	char **ret_split;

	all->hist[all->qtd_hist] = malloc((2048 + 1) * sizeof(char*));
	ft_memcpy(all->hist[all->qtd_hist],ret,ft_strlen(ret));
	all->qtd_hist++;

	printf ("\n");
	//ret = ft_strtrim(ret, " ");
		comandos = ft_split(ret,';');
		i = 0;
		while (comandos[i] != NULL || i == 0 )
		{
			if (comandos[i] == NULL)
			{
				// chama cabecalho da linha novamente
				break;
			}
			ret_split = ft_split(comandos[i],' ');
			if (ft_strncmp(ret_split[0],"pwd",3) == 0 && ft_strlen(ret_split[0]) == 3)
				printf("%s\n",get_pwd(ret_split));
			else if(ft_strncmp(ret_split[0],"ls",2) == 0 && ft_strlen(ret_split[0]) == 2)
				ls();
			else if(ft_strncmp(ret_split[0],"echo",4) == 0 && ft_strlen(ret_split[0]) == 4)
				printf("%s\n",get_echo(ret_split));
			else if(ft_strncmp(ret_split[0],"cd",2) == 0 && ft_strlen(ret_split[0]) == 2)
				printf("%s\n",get_cd(ret_split,all));
			else if(ft_strncmp(ret_split[0],"unset",5) == 0 && ft_strlen(ret_split[0]) == 5)
				all->var_ambiente = exc_var(all->var_ambiente,ret_split);
			else if(ft_strncmp(ret_split[0],"export",6) == 0 && ft_strlen(ret_split[0]) == 6)
				all->var_ambiente = get_export(all->var_ambiente,ret_split);
			else if(ft_strncmp(ret_split[0],"env",3) == 0 && ft_strlen(ret_split[0]) == 3)
				ler_export(all->var_ambiente);
			else if (ft_strncmp(ret_split[0],"clear",5) == 0 && ft_strlen(ret_split[0]) == 5)
				tputs(clear_screen,1,my_termprint);
			else if (ft_strncmp(ret_split[0],"lista",5) == 0 && ft_strlen(ret_split[0]) == 5)
				//lista_hist(all);
				printf("retorno = %s\n", loc_var(all->var_ambiente,"cezar"));
			else if(ft_strncmp(ret_split[0],"exit",4) == 0 && ft_strlen(ret_split[0]) == 4)
			{
				printf("Saindo\n");
				exit(0);
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
