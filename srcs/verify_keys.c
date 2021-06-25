/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:18:27 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/24 17:11:48 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* teclas especiais */
/* \e[A = CIMA      */
/* \e[B = BAIXO     */
static void	verify_up_down(t_v *all, char *ret)
{
	tputs(tgoto(tgetstr("ch", NULL), 0,
			(int)ft_strlen(all->prompt)), 0, &my_termprint);
	tputs(tigetstr("ed"), 1, my_termprint);
	free(all->ret2);
	if (!ft_strncmp("\e[A", ret, 3))
	{
		if (all->posic_hist > 0)
			all->posic_hist--;
		all->ret2 = ft_strdup(all->hist[all->posic_hist]);
	}
	if (!ft_strncmp("\e[B", ret, 3))
	{
		all->posic_hist ++;
		if (all->posic_hist >= all->qtd_hist)
			all->ret2 = ft_strdup("");
		else
			all->ret2 = ft_strdup(all->hist[all->posic_hist]);
	}
	verify_limits(all);
	all->pos_str = ft_strlen(all->ret2);
	all->size = ft_strlen(all->ret2);
	ret[0] = 0;
}

/* teclas especiais */
/* \e[C = DIREITA   */
/* \e[D = ESQUERDA  */
/* \e[H = HOME      */
/* \e[F = END       */
/* \e[ =  OUTRAS    */
/* **               */
static void	verify_left_right(t_v *all, char *ret)
{
	if (!ft_strncmp("\e[C", ret, 3))
	{
		if (all->pos_str < (int)ft_strlen(all->ret2))
			all->pos_str++;
		tputs(tgoto(tgetstr("ch", NULL), 0, all->pos_str
				+ (int)ft_strlen(all->prompt)), 0, &my_termprint);
		tputs(save_cursor, 1, my_termprint);
		ret[0] = 0;
	}
	if (!ft_strncmp("\e[D", ret, 3))
	{
		if (all->pos_str > 0)
			all->pos_str--;
		tputs(tgoto(tgetstr("ch", NULL), 0, all->pos_str
				+ (int)ft_strlen(all->prompt)), 0, &my_termprint);
		tputs(save_cursor, 1, my_termprint);
	}
}

/* teclas especiais */
/* 28 = CTRL - /    */
/* 3 = CTRL - C     */
/* 4 = CTRL - D     */
/* 127 = BACKSPACE  */
/* 51 = DELETE      */
/* **               */
static void	verify_back(t_v *all, char *ret)
{
	if (ret[0] == 127 || ret[2] == 51 )
	{
		if (all->pos_str > 0)
		{
			if (ret[0] == 127)
			{
				erase_bksp(all, all->pos_str);
				all->pos_str--;
			}
			if (ret[2] == 51)
				erase_bksp(all, all->pos_str + 1);
		}
		ret[0] = 0;
		tputs(tgoto(tgetstr("ch", NULL), 0,
				(int)ft_strlen(all->prompt)), 0, &my_termprint);
		tputs(tigetstr("ed"), 1, my_termprint);
		all->ret2[ft_strlen(all->ret2)] = 0;
		ft_putstr_fd(all->ret2, 1);
		tputs(tgoto(tgetstr("ch", NULL), 0, (int)ft_strlen(all->prompt)
				+ all->pos_str), 0, &my_termprint);
		all->size--;
	}
}

static void	verify_home_end(t_v *all, char *ret)
{
	if (!ft_strncmp("\e[H", ret, 3))
	{
		all->pos_str = (int)ft_strlen(all->prompt);
		tputs(tgoto(tgetstr("ch", NULL), 0, all->pos_str), 0, &my_termprint);
		all->pos_str = 0;
	}
	if (!ft_strncmp("\e[F", ret, 3))
	{
		all->pos_str = (int)ft_strlen(all->ret2) + (int)ft_strlen(all->prompt);
		tputs(tgoto(tgetstr("ch", NULL), 0, all->pos_str), 0, &my_termprint);
		all->pos_str = ft_strlen(all->ret2);
	}
}

int	verify_term(t_v *all, char *ret)
{
	verify_left_right(all, ret);
	if (!ft_strncmp("\e[A", ret, 3) || !ft_strncmp("\e[B", ret, 3))
		verify_up_down(all, ret);
	else
	{
		if (ret[0] == 3)
		{
			ft_putstr_fd("^C\n", 1);
			ft_bzero(all->ret2, ft_strlen(all->ret2));
			write_prompt(all);
		}
		if (ret[0] == 4 )
		{
			if (ft_strlen(all->ret2) == 0 )
			{
				ft_putstr_fd("\n", 1);
				tcsetattr(0, TCSANOW, &all->old);
				bye(all);
			}
		}
		verify_back(all, ret);
		verify_home_end(all, ret);
	}
	return (!ft_isprint(ret[0]));
}
