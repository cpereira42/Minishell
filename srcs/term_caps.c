/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:20:26 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/26 12:01:17 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	long	size;
	char	*pwd;
	char	*aux;

	if (signum == SIGINT)
	{
		printf("^Cf\n");
		size = MIL;
		pwd = NULL;
		pwd = getcwd(pwd, (size_t)size);
		aux = get_last_path(pwd);
		aux = ft_strjoin(aux, "> ");
		ft_putstr_fd("\033[1;34m", 1);
		ft_putstr_fd(aux, 1);
		ft_putstr_fd("\033[0;37m", 1);
		tputs(tigetstr("ce"), 1, my_termprint);
		tputs(save_cursor, 1, my_termprint);
		free(pwd);
		free(aux);
	}
}

void	sighandlerchild(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	if (signum == SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	config_term(t_v *all)
{
	char	ret[2048];

	tgetent(ret, getenv("TERM"));
	tcgetattr(0, &all->old);
	tcgetattr(0, &all->term);
	tcgetattr(0, &all->intterm);
	signal(SIGINT, sighandler);
	all->term.c_lflag &= ~(ECHO);
	all->term.c_lflag &= ~(ICANON);
	all->term.c_lflag &= ~(ISIG);
	all->term.c_cc[VMIN] = 1;
	all->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &all->term);
	all->intterm.c_lflag &= ~(ECHO);
	all->intterm.c_lflag &= ~(ICANON);
	all->intterm.c_cc[VMIN] = 1;
	all->intterm.c_cc[VTIME] = 0;
}

int	my_termprint(int c)
{
	return (write(1, &c, 1));
}

void	verify_limits(t_v *all)
{
	if (all->posic_hist > all->qtd_hist)
		all->posic_hist = all->qtd_hist;
	if (all->posic_hist < 0)
		all->posic_hist = 0;
	ft_putstr_fd(all->ret2, 1);
}
