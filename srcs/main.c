#include <unistd.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>
#include "minishell.h"
#include "../libft/libft.h"
#include "../includes/get_next_line.h"

int	verify_char(char *line, char letter)
{
	char	**ret;
	int		i;
	int		error;

	i = 0;
	error = 0;
	ret = ft_split3(line, letter);
	while (i < count_split(ret))
	{
		if (ft_strlen(ret[i]) == 0)
			error++;
		i++;
	}
	free_array((void *)ret);
	return (error);
}

int	verify_line(char *line)
{
	int		error;
	char	*aux;

	aux = ft_strdup(line);
	error = verify_char(aux, '|');
	error += verify_char(aux, '>');
	error += verify_char(aux, '<');
	check_n_free(aux);
	if (error > 0)
	{
		printf("Sintax error\n");
		return (0);
	}
	return (1);
}

int	main(void)
{
	t_v	v;

	configs(&v, __environ);
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		tcsetattr(0, TCSAFLUSH, &v.term);
		ft_bzero(v.ret, 2048);
		read (0, v.ret, 100);
		if (!verify_term(&v, v.ret) || !ft_strncmp("\n", v.ret, 1))
		{
			if (!ft_strncmp("\n", v.ret, 1))
				processing(&v);
			else
				add_key(&v);
			if (v.r_command == 3)
			{
				u_free_array_bi(&v.ret2);
				bye(&v);
			}
		}
	}
	return (0);
}

void	add_key(t_v *v)
{
	v->ret2[v->pos_str] = v->ret[0];
	if (v->pos_str < (int)ft_strlen(v->ret2))
		v->size++;
	v->pos_str++;
	ft_putstr_fd(v->ret, 1);
}

void	processing(t_v *v)
{
	v->ret_last = 0;
	v->ret2[v->size] = '\0';
	v->posic_hist = v->qtd_hist;
	v->pos_str = 0;
	add_hist(v, v->ret2);
	v->flag_exit = 0;
	ft_putstr_fd("\n", 1);
	if (ft_strlen(v->ret2) > 1 && v->ret2[0] != '>' && v->ret2[0] != '<'
		&& verify_line(v->ret2))
		parse_cmd_lines(v, v->ret2, 0);
	write_prompt(v);
	ft_bzero(v->ret, 2048);
	ft_bzero(v->ret2, ft_strlen(v->ret2) + 1);
	if (v->flag_exit == 1)
		bye(v);
	v->size = 0;
}
