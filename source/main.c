/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:20:18 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/20 16:07:03 by cpereira         ###   ########.fr       */
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
	ft_putstr_fd(ptr,1);
	return (ptr);
}
int		count_pipe(char *ret, char c)
{
	int i;
	int qtd;

	i = 0;
	qtd = 0;
	while (ret[i] != '\0')
	{
		if (ret[i] == c)
			qtd++;
		i++;
	}
	return (qtd);
}

void get_echo (char **ret, t_all *all, int fd)
{
	char *ptr;
	char *termo;
	int i;
	int flag;
	int count;

	i = 1;
	flag = 0;
	count = 0;
	ptr = ft_strdup("");

	while (ret[i] != NULL)
	{
		if (ret[i][0]== '$')
			termo = loc_var(all->var_ambiente,&ret[i][1],all);
		else
			termo = ft_strdup(ret[i]);

		if (termo[0] == '"' || termo[0] == '\'' )
			termo = termo[0] == '"' ? ft_strtrim(termo,"\""): ft_strtrim(termo,"'") ;
		if (ft_strncmp(ret[i], "-n", 2) == 0 && count == 0)
			flag = 1;
		else
		{
			if (i-flag != 1 && count != 0 )
				ptr = ft_strjoin (ptr, " ");
			ptr = ft_strjoin (ptr,termo);
			count ++;
		}
		i++;
	}
	if (flag == 1)
		ptr = ft_strjoin (ptr,"%");

	if (all->qtd_pipe == 0 || all->qtd_pipe == all->posic_pipe)
	{
		ft_putstr_fd(ptr,fd);
		ft_putstr_fd("\n",fd);
	}
	else
	{
		fd = open("arq1", O_CREAT | O_WRONLY | O_TRUNC, 444);
		if (!fd)
			ft_putstr_fd("Erro ao gerar arquivo", 1);
		else
			ft_putstr_fd(ptr, fd);
		close(fd);
		//all->posic_pipe++;
		all->ret_aux = ptr;
		//execulta_comando (all->pipe_split[all->posic_pipe],all);
	}
	//return (ptr);
}

int get_pwd (char **ret, t_all *all, int fd)
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

	if (all->qtd_pipe == 0 || all->qtd_pipe == all->posic_pipe)
	{
		ft_putstr_fd(ptr,fd);
		ft_putstr_fd("\n",fd);
	}
	else
	{
		fd = open("arq1", O_CREAT | O_WRONLY | O_TRUNC, 444);
		if (!fd)
			ft_putstr_fd("Erro ao gerar arquivo", 1);
		else
			ft_putstr_fd(ptr, fd);
		close(fd);
		//all->posic_pipe++;
		all->ret_aux = ptr;
		//execulta_comando (all->pipe_split[all->posic_pipe],all);
	}


	//ft_putstr_fd(ptr,1);
	return (0);
}

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

void sighandler(int signum)
{
	if (signum == 18)
		printf("Ctrl = C\n");

	if (signum == 2)
	{
		exit (0);
	}
	if (signum == 3)
	{
		printf("Ctrl = a\n");
		exit (0);
	}

	//printf("Caught signal %d, coming out...\n", signum);

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

int teste_fork(t_all *all, char **args)
{
	int i;
	//int in_fd;
	//int out_fd;
	pid_t	pid;
	int status;
	char *comando;
	int filedesc;


	if (all->qtd_pipe == 0)
		;
	printf("Args *%s*\n",args[1]);

	args[1] = ft_strtrim(args[1],"\"");
	args[2] = "arq1";
	args[3] = NULL;


	int save_in = dup(STDIN_FILENO);
	int save_out = dup(STDOUT_FILENO);

	filedesc = open("arq1", O_WRONLY , 0644);
	if (all->posic_pipe < all->qtd_pipe)
	{
		dup2(filedesc, STDOUT_FILENO);
		close(filedesc);
	}

	i = 0;
	if ((pid = fork()) < 0)
			;//message_and_exit(ERRSYS, NULL);
	else if (pid == 0)
	{
		//file_descriptor_handler(in_fd, out_fd);
		while (all->path[i] != NULL  )
		{
			comando = ft_strdup(all->path[i]);
			comando = ft_strjoin(comando,"/");
			comando = ft_strjoin(comando,args[0]);
			//printf("commando = %s\n",comando);
			//comando = "/usr/bin/sed";
			//argse[0] = comando;
			//argse[0] = "/usr/bin/sed";
			execve(comando, &args[0] ,all->var_ambiente);
			i++;
		}
		//in_fd = all->pp[0];
	}
	else
		waitpid(pid, &status, 0);

	//if (all->posic_pipe == all->qtd_pipe)

	//ft_putstr_fd("teste",filedesc);
	//dup2(save_in, STDIN_FILENO);
	save_in = 0;
	dup2(save_out, STDOUT_FILENO);
	//dup2(filedesc, STDOUT_FILENO);
	close(filedesc);


	//fd = open("arq1", O_CREAT | O_WRONLY | O_TRUNC, 444);

	//if (all->posic_pipe == all->qtd_pipe)
	//	file_descriptor_handler(in_fd, STDOUT_FILENO);
	return (0);
}

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}

int teste_fork_BKP(t_all *all, char **args)
{
	int i;

	char *comando;

	int filedesc;
	filedesc = open("arq1", O_WRONLY , 0644);

	if (all->qtd_pipe == 0)
		;
	printf("Args *%s*\n",args[1]);

	args[1] = ft_strtrim(args[1],"\"");
	args[2] = "arq1";
	args[3] = NULL;

	int save_in = dup(STDIN_FILENO);
	int save_out = dup(STDOUT_FILENO);

	if (all->posic_pipe < all->qtd_pipe)
	{
		dup2(filedesc, STDOUT_FILENO);
		close (filedesc);
	}



	i = 0;
	if ( fork() == 0 )
	{
		while (all->path[i] != NULL  )
		{
			comando = ft_strdup(all->path[i]);
			comando = ft_strjoin(comando,"/");
			comando = ft_strjoin(comando,args[0]);
			//printf("commando = %s\n",comando);
			//comando = "/usr/bin/sed";
			//argse[0] = comando;
			//argse[0] = "/usr/bin/sed";
			execve(comando, &args[0] ,all->var_ambiente);
			i++;
		}
		//return(1);
	}
	filedesc = open("arq2", O_CREAT | O_WRONLY | O_TRUNC, 444);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(filedesc);

	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_all all;


	char ret[2048];
	reseta_flags(&all, env);
    tgetent(ret, getenv("TERM"));

	struct termios term;
	struct termios old;
	tcgetattr(0,&old);
	tcgetattr(0,&term);



	signal( SIGINT, sighandler );

	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ISIG);
	term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;

	//term.c_cc[VINTR] = 4; // ^D
	//term.c_cc[VSUSP]  = 3;
	//term.c_cc[VEOF]  = 3;

	//term.c_cc[SIGQUIT]  = 9; // ^C // 3
	//term.c_cc[VSUSP]  = 3;
	tcsetattr(0,TCSANOW,&term);


	//printf("== %d\n",VQUIT);

	//tcsetattr(0,TCSANOW,&term);
	//signal(SIGINT, sighandler);
	//signal(SIGTSTP, sighandler);
	//signal(SIGQUIT, sighandler);
	//signal(VSUSP,sighandler);
	//VSUSP
	//signal(1, sighandler);

	//signal(SIGINT, SIG_IGN);

	all.ac = ac;
	all.av = av;

	//printf ("env = %s av = %s ac = %d\n", env[1],av[0],ac);

	ft_putstr_fd("Bem vindo ao MINISHELL CPEREIRA & PCUNHA\n",1);

	ft_putstr_fd(all.cabecalho,1);

	tputs(tigetstr("ce"),1,my_termprint); // ed
	tputs(save_cursor,1,my_termprint);
	//tcsetattr(0,TCSANOW,&old);


	//char* arr[] = {"ls", "-l", "-R", "-a", NULL};
	//tcsetattr(0,TCSANOW,&old);



	int pp[2];
	pipe(pp);
	//dup2(pp[IN], STDOUT_FILENO);	// JOGA STDOUT PARA ENTRADA DO PIPE
	//dup2(pp[OUT], STDIN_FILENO);


	/*char *argse[5] ;
	char *commandos;
	commandos = ft_strdup("/usr/bin/sed");
	argse[0] = "/usr/bin/sed";
    argse[1] = "s/hello/hi/";
	argse[2] = "arq1";
	argse[3] = 0;

	//dup2(pp[0], STDOUT_FILENO);	// JOGA STDOUT PARA ENTRADA DO PIPE
	//dup2(pp[1], STDIN_FILENO);
	//ft_putstr_fd("hello there\n",pp[1]);
	execve(commandos, &argse[0] ,all.var_ambiente);*/
	//write(, , 4);

	//





	int processo;
	processo = 1;

  	while (1)
	{
		ft_bzero(ret,2048);
		read (0,ret,100);

		//printf("letra = %d\n",ret[0]);

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
		else if (ret[0] == 3) // baixo
		{
			ft_bzero(all.ret2,2048);
			ft_bzero(all.ret,2048);
			ft_putstr_fd("\n",1);
			ft_putstr_fd(all.cabecalho,1);
			tputs(save_cursor,1,my_termprint);

		}
		else if (ret[0] == 4) // baixo
		{
			ft_putstr_fd("\n",1);
			tcsetattr(0,TCSANOW,&old);
			exit(0);
		}
		else if (ret[0] == 28 && processo == 1) // baixo
		{
			//tcsetattr(0,TCSANOW,&old);
			//exit(1);
			ft_putstr_fd("^\\Quit: 3\n",1);
			//printf("");
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
			all.r_comando = execulta_comando (all.ret2,&all);
			ft_bzero(all.ret2,2048);
			ft_bzero(all.ret,2048);
			ft_putstr_fd(all.cabecalho,1);
			tputs(save_cursor,1,my_termprint);
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
		if (all.r_comando == 3)
		{
			printf("Saindo\n");
			tcsetattr(0,TCSANOW,&old);
			exit(0);
		}
	}
	return (0);
}

int		execulta_comando (char *ret, t_all *all)
{
	char **comandos;
	int i;
	char **ret_split;
	char **ret_split2;
	int filedesc;

	all->hist[all->qtd_hist] = malloc((2048 + 1) * sizeof(char*));
	ft_memcpy(all->hist[all->qtd_hist],ret,ft_strlen(ret));
	all->hist[all->qtd_hist][ft_strlen(ret)]= '\0';
	all->qtd_hist++;

		comandos = ft_split(ret,';');
		i = 0;
		while (comandos[i] != NULL || i == 0 )
		{
			all->posic_pipe = 0;
			if (comandos[i] == NULL)
			{
				// chama cabecalho da linha novamente
				break;
			}
			if (i == 0)
				printf("\n");
			all->pipe_split = ft_split (comandos[i],'|');
			all->qtd_pipe = count_pipe(comandos[i],'|');
			all->posic_pipe = 0;
			//printf("%d %d %s",all->qtd_pipe,all->posic_pipe,all->pipe_split[0]);
			while (all->qtd_pipe >= all->posic_pipe)
			{
				//printf("qtd_pipes = %d\n",all->qtd_pipe);
				ret_split = ft_split(all->pipe_split[all->posic_pipe],' ');
				if(ret_split[0][0] == '$')
					ret_split[0] = loc_var(all->var_ambiente,&ret_split[0][1],all);
				if (ft_strncmp(ret_split[0],"pwd",3) == 0 && ft_strlen(ret_split[0]) == 3)
					get_pwd(ret_split,all,1);
				//else if(ft_strncmp(ret_split[0],"ls",2) == 0 && ft_strlen(ret_split[0]) == 2)
				//	teste_fork(all,ret_split);
				else if(ft_strncmp(ret_split[0],"echo",4) == 0 && ft_strlen(ret_split[0]) == 4)
					get_echo(ret_split,all,1);
				else if(ft_strncmp(ret_split[0],"cd",2) == 0 && ft_strlen(ret_split[0]) == 2)
					get_cd(ret_split,all);
				else if(ft_strncmp(ret_split[0],"unset",5) == 0 && ft_strlen(ret_split[0]) == 5)
					exc_var(ret_split, all);
				else if(ft_strncmp(ret_split[0],"export",6) == 0 && ft_strlen(ret_split[0]) == 6)
					export_var(all,ret_split);
				else if(ft_strncmp(ret_split[0],"env",3) == 0 && ft_strlen(ret_split[0]) == 3)
					ler_export(all->var_ambiente);
				else if (ft_strncmp(ret_split[0],"clear",5) == 0 && ft_strlen(ret_split[0]) == 5)
					tputs(clear_screen,1,my_termprint);
				else if (ft_strncmp(ret_split[0],"lista",5) == 0 && ft_strlen(ret_split[0]) == 5)
					lista_hist(all);
				else if (ft_strpos(comandos[i],'>') > 0)
				{
					ret_split2 = ft_split(comandos[i],'>');
					filedesc = open(ret_split2[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
					ft_putstr_fd(ret_split2[0],filedesc);
					close(filedesc);
					//printf(" %s > %s \n",ret_split2[1],ret_split2[0]);
				}

					//lista_hist(all);

					//printf("retorno = %s\n", loc_var(all->var_ambiente,"cezar"));
				else if(ft_strncmp(ret_split[0],"exit",4) == 0 && ft_strlen(ret_split[0]) == 4)
					return(3);
				else
				{
					if (teste_fork(all,ret_split))
						printf ("Command not found\n");
					ft_bzero(ret,2048);
				}
				all->posic_pipe++;
			}
			i++;
		}
		//free_array((void*)comandos);
		return(0);
}
