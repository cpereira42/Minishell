/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:20:26 by cpereira          #+#    #+#             */
/*   Updated: 2021/05/03 16:25:31 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/main.h"
#include "../includes/libft.h"

#include <stdio.h>
#include <curses.h>

void config_term(t_all *all)
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


int verify_term(t_all *all, char *ret)
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
		return (1);
	}
	if (!ft_strncmp("\e[B",ret,3)) // baixo
	{
		tputs(restore_cursor,1,my_termprint);
		tputs(tigetstr("ed"),1,my_termprint);
		all->ret2 = ft_strdup(all->hist[all->posic_hist]);
		ft_putstr_fd(all->ret2,1);
		if (all->posic_hist >= all->qtd_hist - 1)
			all->posic_hist = all->qtd_hist - 1;
		else
			all->posic_hist ++;
		ret[0] = 0;
		return (1);
	}
	if (!ft_strncmp("\e[C",ret,3)) //  direita
	{
		tputs(restore_cursor,1,my_termprint);
		tputs(tigetstr("ed"),1,my_termprint); // ed
		ft_putstr_fd("cc",1);
		//ft_bzero(ret,2048);
		//ret2 = ft_strdup("");
		//write (1,"dir\n",3);
		ret[0] = 0;
		return (1);
	}
	else if (!ft_strncmp("\e[D",ret,3)) //  esquerda
	{

		tputs(restore_cursor,1,my_termprint);
		tputs(tigetstr("ed"),1,my_termprint);
		ft_putstr_fd("dd",1);
		////tputs(clear_screen,1,my_termprint);
		//ft_bzero(ret,2048);
		//ret2 = ft_strdup("");
		//write (1,"esq\n",3);
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
		ft_bzero(all->ret2,2048);
		ft_bzero(all->ret,2048);
		ft_putstr_fd("\n",1);
		ft_putstr_fd(all->cabecalho,1);
		tputs(save_cursor,1,my_termprint);

	}
	if (ret[0] == 4) // CTRL +D
	{
		ft_putstr_fd("Logout\n",1);
		tcsetattr(0,TCSANOW,&all->old);
		exit(0);
	}




	//ft_putnbr_fd(ret[0],1);
	//ft_putstr_fd(ret,1);

	return (0);



}
