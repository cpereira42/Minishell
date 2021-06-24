/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:26:45 by cpereira          #+#    #+#             */
/*   Updated: 2021/06/23 19:09:42 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_hist(t_v *all, char *ret)
{
	all->pos_str = 0;
	all->flag_exit = 0;
	all->hist[all->qtd_hist] = malloc ((int)(ft_strlen(ret) + 1)
			* sizeof(char *));
	ft_memcpy(all->hist[all->qtd_hist], ret, ft_strlen(ret));
	all->hist[all->qtd_hist][ft_strlen(ret)] = '\0';
	all->qtd_hist++;
	all->posic_hist = all->qtd_hist;
}

void	add_samples(t_v *v)
{
	add_hist(v, "pwd ; pwd a");
	add_hist(v, "xx yy |  >a1 <a2 abc  >a3 < a4 | aa arg1 arg2; z > a5'");
	add_hist(v, "echo \'asd\'     \"djfjdkf\" $PWD \"$PWD\" \'$PWD\'");
	add_hist(v, "cd srcs | pwd >> arq");
	add_hist(v, "echo \'asd\'  $PWD \"$PWD\" \'$PWD\'; lixo a b c");
	add_hist(v, "export a=234; export b=567");
	add_hist(v, "export a=234; export b=567; unset a");
	add_hist(v, "env; export a=234; export b=567; unset a; ls -la | grep mini");
	add_hist(v, "echo \"ls -la");
	add_hist(v, "ls");
	add_hist(v, "ls -la | grep a | grep k");
	add_hist(v, "echo $?; ls -la | grep a | grep k; echo $?");
	add_hist(v, "echo cezar | sed \"s/cezar/angelica/\"");
	add_hist(v, "echo daniel | sed \"s/cezar/angelica/\"");
	add_hist(v, "echo \"cezar | angelica \"");
	add_hist(v, "echo \"cezar > angelica \"");
	add_hist(v, "echo ola mundo -n");
	add_hist(v, "echo -n -n ola mundo");
	add_hist(v, "echo -n ola mundo");
	add_hist(v, "ls;la;ls");
	add_hist(v, "cd / ; ls -Rla");
	add_hist(v, "$?");
	add_hist(v, "ls; echo $?; la ; echo $?; ls ; echo $?");
	add_hist(v, "echo cezar | sed \"s/cezar/angelica/\" | sed \"s/angelica/42/\"");
}
