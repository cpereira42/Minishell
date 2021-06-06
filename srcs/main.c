# include <unistd.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include "minishell.h"
# include "../libft/libft.h"
# include "../includes/get_next_line.h"

void write_error(t_v *v)
{
	ft_putstr_fd("bash *: ",1);
	ft_putstr_fd(v->curr_comand,1);
	v->cmd.ret_status = 127;
	v->flag_exit = 1;
	ft_putstr_fd(" : command not found\n",1);
}

void write_return(t_v *v)
{
	ft_putstr_fd("zsh : command not found : ",1);
	ft_putnbr_fd(v->cmd.ret_status,1);
	ft_putstr_fd("\n",1);
	v->ret_last = 1;
}

void write_prompt(t_v *v)
{
	ft_putstr_fd("\033[1;34m",1);
	ft_putstr_fd(v->prompt,1);
	ft_putstr_fd("\033[0;37m",1);
	tputs(tigetstr("ce"),1,my_termprint); // ed
	tputs(save_cursor,1,my_termprint);
}

int	main(void)
{
	t_v v;

	init_env(&v, __environ);
	init_path(&v);
	reset_flags(&v);
	if(v.qtd_hist == 0)
		add_samples(&v);
	create_prompt(&v);
	write_prompt(&v);
	v.flag_perm_denied = 0;

	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		ft_bzero(v.ret,2048);
		read (0,v.ret,100);
		if (!verify_term(&v,v.ret,0))
		{
			if (!ft_strncmp("\n",v.ret,1))
			{
				v.ret_last = 0;
				v.ret2[v.size] = '\0';
				v.posic_hist = v.qtd_hist;
				v.posic_string = 0;
				add_hist(&v,v.ret2);
				v.flag_exit = 0;
				ft_putstr_fd("\n",1);
				if (ft_strlen(v.ret2) > 1 && v.ret2[0] != '>' && v.ret2[0] != '<')
					parse_cmd_lines(&v, v.ret2, 0);
				if (v.flag_exit == 1)
					bye(&v);
				write_prompt(&v);
				ft_bzero(v.ret,2048);
				ft_bzero(v.ret2,ft_strlen(v.ret2) + 1);
			}
			else
			{
				v.ret2[v.posic_string] = v.ret[0];
				v.size = ft_strlen(v.ret2);
				v.posic_string++;
				ft_putstr_fd(v.ret,1);
			}
			if (v.r_command == 3)
			{
				u_free_array_bi(&v.ret2);
				bye(&v);
			}
		}
	}
	return (0);
}

