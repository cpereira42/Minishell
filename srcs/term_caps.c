/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:20:26 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/05 16:23:03 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	long	size;
	char	*pwd;
	char	*aux;

	if (signum == 18 || signum == 3)
		;
	size = MIL;
	pwd = NULL;
	pwd = getcwd(pwd, (size_t)size);
	aux = get_last_path(pwd);
	aux = ft_strjoin(aux, "> ");
	printf("\n");
	ft_putstr_fd("\033[1;34m",1);
	ft_putstr_fd(aux,1);
	ft_putstr_fd("\033[0;37m",1);
	tputs(tigetstr("ce"),1,my_termprint); // ed
	tputs(save_cursor,1,my_termprint);
	free(pwd);
	free(aux);
}

void	sighandlerchild(int signum)
{
	if (signum == 18 || signum == 3)
		;
	printf("^C\n");
}


void	config_term(t_v *all)
{
	char	ret[2048];

	tgetent(ret, getenv("TERM"));
	tcgetattr(0, &all->old);
	tcgetattr(0, &all->term);
	signal(SIGINT, sighandler);
	all->term.c_lflag &= ~(ECHO);
	all->term.c_lflag &= ~(ICANON);
	//all->term.c_lflag &= ~(ISIG);
	all->term.c_cc[VMIN] = 1;
	all->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &all->term);
}

int	my_termprint(int c)
{
	return (write(1, &c, 1));
}

void verify_limits(t_v *all)
{
	if (all->posic_hist > all->qtd_hist)
		all->posic_hist = all->qtd_hist;
	if (all->posic_hist < 0)
		all->posic_hist = 0;
}

static int verify_up_down(t_v *all, char *ret, int out)
{
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(int)ft_strlen(all->prompt)), 0, &my_termprint);
	tputs(tigetstr("ed"), 1, my_termprint);
	free(all->ret2);
	if (!ft_strncmp("\e[A", ret, 3)) /* ** cima */
	{
		if (all->posic_hist > 0)
			all->posic_hist--;
		all->ret2 = ft_strdup(all->hist[all->posic_hist]);
		out = 1;
	}
	if (!ft_strncmp("\e[B", ret, 3)) /* ** baixo */
	{
		all->posic_hist ++;
		if (all->posic_hist >= all->qtd_hist)
			all->ret2 = ft_strdup("");
		else
			all->ret2 = ft_strdup(all->hist[all->posic_hist]);
		out = 1;
	}
	verify_limits(all);
	ft_putstr_fd(all->ret2, 1);
	all->posic_string = ft_strlen(all->ret2);
	ret[0] = 0;
	return (out);
}

static int	verify_left_right(t_v *all, char *ret)
{
	if (!ft_strncmp("\e[C", ret, 3)) /* **  direita */
	{
		if (all->posic_string < (int)ft_strlen(all->ret2))
			all->posic_string++;
		tputs(tgoto(tgetstr("ch", NULL), 0, all->posic_string
				+ (int)ft_strlen(all->prompt)), 0, &my_termprint);
		tputs(save_cursor, 1, my_termprint);
		ret[0] = 0;
		return (1);
	}
	if (!ft_strncmp("\e[D", ret, 3)) /* **  esquerda */
	{
		if (all->posic_string > 0)
			all->posic_string--;
		tputs(tgoto(tgetstr("ch", NULL), 0, all->posic_string
				+ (int)ft_strlen(all->prompt)), 0, &my_termprint);
		tputs(save_cursor, 1, my_termprint);
		return (1);
	}

	if (!ft_strncmp("\e[", ret, 2)) /* ** teclas extras */
			return (1);

	if (!ft_strncmp("\e[H", ret, 3)) /* **  home */
	{
		all->posic_string = (int)ft_strlen(all->prompt);
		tputs(tgoto(tgetstr("ch", NULL), 0, all->posic_string), 0, &my_termprint);
		all->posic_string --;
		return (1);
	}
	if (!ft_strncmp("\e[F", ret, 3)) /* **  end */
	{
		all->posic_string = (int)ft_strlen(all->ret2) + (int)ft_strlen(all->prompt);
		tputs(tgoto(tgetstr("ch", NULL), 0, all->posic_string ), 0, &my_termprint);
		all->posic_string ++;
		return (1);
	}
	if (!ft_strncmp("\e[", ret, 2)) /* ** teclas extras */
			return (1);
	return (0);
}

int	verify_term(t_v *all, char *ret, int out)
{
	out = verify_left_right(all, ret);
	if (!ft_strncmp("\e[A", ret, 3) || !ft_strncmp("\e[B", ret, 3))
		out = verify_up_down(all, ret, 0);
	else
	{
		if (ret[0] == 3) /* ** CTRL C */
		{
			ft_putstr_fd("\n", 1);
			write_prompt(all);
			//printf("ola mundo\n");
			//
			//tcsetattr(0, TCSANOW, &all->old);
			//bye(all);
		}

		if (ret[0] == 4) /* ** CTRL D */
		{
			if (all->pidc != all->pid)
			{
				ft_putstr_fd("\n", 1);
				tcsetattr(0, TCSANOW, &all->old);
				bye(all);
			}
			else
				return 0;
		}
		if (ret[0] == 127) /* **backspace */
		{
			if (all->posic_string > 0)
				all->posic_string--;
			ret[0] = 0;
			tputs(restore_cursor, 1, my_termprint);
			tputs(tigetstr("ed"), 1, my_termprint);
			all->ret2[ft_strlen(all->ret2) - 1] = 0;
			ft_putstr_fd(all->ret2, 1);
			out = 1;
		}
	}
	return (out);
}

