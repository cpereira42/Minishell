/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:23:26 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 17:34:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	config_term(t_v *v)
{
	char	ret[2048];

	tgetent(ret, getenv("TERM"));
	tcgetattr(0, &v->old);
	tcgetattr(0, &v->term);
	signal(SIGINT, sighandler);
	v->term.c_lflag &= ~(ECHO);
	v->term.c_lflag &= ~(ICANON);
	v->term.c_lflag &= ~(ISIG);
	v->term.c_cc[VMIN] = 1;
	v->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &v->term);
}
