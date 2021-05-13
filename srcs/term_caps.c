/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:20:26 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/12 16:58:53 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sighandler(int signum)
{
	if (signum == 18)
		printf("Ctrl = C\n");

	if (signum == 2)
		exit (0);
	if (signum == 3)
	{
		printf("Ctrl = a\n");
		exit (0);
	}
	//printf("signal %d\n",signum);
	printf("Caught signal %d, coming out...\n", signum);
}

void config_term(t_v *all)
{
	char ret[2048];
	tgetent(ret, getenv("TERM"));
	tcgetattr(0,&all->old);
	tcgetattr(0,&all->term);
	signal( SIGINT, sighandler );
	all->term.c_lflag &= ~(ECHO);
	all->term.c_lflag &= ~(ICANON);
	all->term.c_lflag &= ~(ISIG);
	all->term.c_cc[VMIN] = 1;
    all->term.c_cc[VTIME] = 0;
	tcsetattr(0,TCSANOW,&all->term);
}

int my_termprint(int c)
{
	return write(1, &c, 1);
}


int verify_term(t_v *all, char *ret)
{
	if (!ft_strncmp("\e[A",ret,3)) // cima
	{
		tputs(restore_cursor,1,my_termprint);
		tputs(tigetstr("ed"),1,my_termprint); //kL
		all->ret2 = ft_strdup(all->hist[all->posic_hist]);
		ft_putstr_fd(all->ret2,1);
		if (all->posic_hist <= 0)
			all->posic_hist = 0;
		else
			all->posic_hist --;
		ret[0] = 0;
		all->posic_string = ft_strlen(all->ret2);

		return (1);
	}
	if (!ft_strncmp("\e[B",ret,3)) // baixo
	{
		tputs(restore_cursor,1,my_termprint);
		tputs(tigetstr("ed"),1,my_termprint);
		if (all->posic_hist <= all->qtd_hist)
		{
			all->ret2 = ft_strdup(all->hist[all->posic_hist]);
			ft_putstr_fd(all->ret2,1);
		}

		if (all->posic_hist >= all->qtd_hist - 1)
			all->posic_hist = all->qtd_hist - 1;
		else
			all->posic_hist ++;
		ret[0] = 0;
		all->posic_string = ft_strlen(all->ret2);
		//printf("hist = %d\n",all->posic_hist);
		return (1);
	}
	if (!ft_strncmp("\e[C",ret,3)) //  direita
	{
		if (all->posic_string < (int)ft_strlen(all->ret2))
			all->posic_string++;
		tputs(tgoto(tgetstr("ch", NULL), 0, all->posic_string + (int)ft_strlen(all->cabecalho)), 0, &my_termprint);
		tputs(save_cursor,1,my_termprint);
		ret[0] = 0;
		return (1);
	}
	else if (!ft_strncmp("\e[D",ret,3)) //  esquerda
	{
		if (all->posic_string > 0)
			all->posic_string--;
		tputs(tgoto(tgetstr("ch", NULL), 0, all->posic_string + (int)ft_strlen(all->cabecalho)), 0, &my_termprint);
		tputs(save_cursor,1,my_termprint);
		ret[0] = 0;
		return (1);
	}
	if (ret[0] == 127) //backspace
	{
		tputs(restore_cursor,1,my_termprint);
		tputs(tigetstr("ed"),1,my_termprint);
		//tputs(tigetstr("kD"),1,my_termprint);
		all->ret2[ft_strlen(all->ret2)-1] = 0;
		ft_putstr_fd(all->ret2,1);
		return (1);
	}
	if (ret[0] == 3) // CTRL+C
	{
		ft_bzero(all->ret2, 2048);
		ft_bzero(all->ret, 2048);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(all->cabecalho,1);
		tputs(save_cursor,1,my_termprint);

	}
	if (ret[0] == 4) // CTRL +D
		exit_msh(all);
	return (0);
}
