/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:20:18 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/03 16:27:52 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>

void add_hist(t_all *all, char *ret)
{
	all->hist[all->qtd_hist] = malloc((2048 + 1) * sizeof(char*));
	ft_memcpy(all->hist[all->qtd_hist],ret,ft_strlen(ret));
	all->hist[all->qtd_hist][ft_strlen(ret)]= '\0';
	all->posic_hist = all->qtd_hist;
	all->qtd_hist++;
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
	printf("signal %d\n",signum);
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



int		main(int ac, char **av, char **env)
{
	t_all all;

	char ret[2048];
	reseta_flags(&all, env);

	config_term(&all);

    /*tgetent(ret, getenv("TERM"));
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
	tcsetattr(0,TCSANOW,&term);*/


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

	ft_putstr_fd("Bem vindo ao MINISHELL CPEREIRA & PCUNHA\n",1);
	ft_putstr_fd(all.cabecalho,1);
	tputs(tigetstr("ce"),1,my_termprint); // ed
	tputs(save_cursor,1,my_termprint);



	int processo;
	processo = 1;

	//add_hist(&all, "pwd | sed \"s/shell/IPIRANGA/\" > tess.txt");

	add_hist(&all, "echo cezar | sed \"s/cezar/angelica/\"");
	add_hist(&all, "echo cezar | sed \"s/cezar/angelica/\" | sed \"s/angelica/42/\"");
	add_hist(&all, "echo daniel | sed \"s/cezar/angelica/\"");
	//add_hist(&all, "echo \"hello there\" > arq | sed \"s/hello/hi/\" | <arq sed \"s/there/robots/\"");
	//add_hist(&all, "echo \"hello there\" > arq");


	while (1)
	{
		ft_bzero(ret,2048);
		read (0,ret,100);

		//printf("letra = %d\n",ret[0]);

		if (!verify_term(&all,ret))
		{
			if (!ft_strncmp("\n",ret,1))
			{
				all.posic_hist = all.qtd_hist;
				all.r_comando = execulta_comando (all.ret2,&all);
				ft_bzero(all.ret2,2048);
				ft_bzero(all.ret,2048);
				ft_putstr_fd("\n",1);
				ft_putstr_fd(all.cabecalho,1);
				tputs(save_cursor,1,my_termprint);
			}
			else
			{
				all.ret2 = ft_strjoin(all.ret2,ret);
				ft_putstr_fd(ret,1);
			}
			if (all.r_comando == 3)
			{
				printf("Logout\n");
				tcsetattr(0,TCSANOW,&all.old);
				exit(0);
			}
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
			//pipe(all->pp);
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
			//while (all->qtd_pipe >= all->posic_pipe)
			//{
				//printf("qtd_pipes = %d\n",all->qtd_pipe);
				//ret_split = ft_split(comandos[0],' '); all->pipe_split
				ret_split = ft_split(all->pipe_split[0],' ');

				if(ret_split[0][0] == '$')
					ret_split[0] = loc_var(all->var_ambiente,&ret_split[0][1],all);
				if (ft_strncmp(ret_split[0],"pwd",3) == 0 && ft_strlen(ret_split[0]) == 3)
					get_pwd(ret_split,all,1);
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
				else if(ft_strncmp(ret_split[0],"exit",4) == 0 && ft_strlen(ret_split[0]) == 4)
					return(3);
				else
				{
					int t;
					t = teste_fork(all);
					if (t)
						printf ("Command not found\n");
					else
						printf("%d\n",t);
					ft_bzero(ret,2048);
				}

				all->posic_pipe++;
			//}
			i++;
		}
		//free_array((void*)comandos);
		return(0);
}
