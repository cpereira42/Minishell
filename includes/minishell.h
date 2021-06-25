/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:19:17 by user42            #+#    #+#             */
/*   Updated: 2021/06/24 20:00:08 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <termcap.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>

# include "libft.h"
# include "get_next_line.h"
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include "dbg.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MIL 1000
# define SPC ' '
# define PIPE_IN 1
# define PIPE_OUT 0

typedef enum e_state_parse_s
{
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}				t_state_parse_s;

typedef struct s_cmd{
	char	*fn;
	char	**cmd_args;
	int		ret_status;
	int		fd_in_red;
	int		fd_out_red;
	int		pipe[2];
	int		save_in;
	int		save_out;
	int		fd_in;
	int		fd_out;
}				t_cmd;

typedef struct s_v{
	char			**cmd_lines;
	char			**pipelines;
	char			*expanded;
	char			**env;
	t_cmd			cmd;
	char			*prompt;
	int				flag_exit;
	char			**path;
	struct termios	intterm;
	struct termios	term;
	struct termios	old;
	char			*hist[50];
	int				qtd_hist;
	int				posic_hist;
	char			*ret2;
	char			ret[2048];
	int				savein;
	int				saveout;
	int				in_fd;
	int				r_command;
	int				pos_str;
	char			*aux;
	pid_t			pid;
	pid_t			pidc;
	char			*curr_comand;
	int				ret_last;
	int				size;
	int				flag_perm_denied;
	int				process;
	int				k;
	int				q;
	int				ax2;
}				t_v;

int		parse_cmd_lines(t_v *v, char *linha, int p);
int		ft_count_lines(char **s);
void	u_free_array_bi(char **s);
int		parse_pipelines(t_v *v, char *linha, int i, int n);
int		parse_s(t_v *v, char *linha);
void	init_env(t_v *v, char **envp);
void	expand(t_v *v, char *linha, int *i, int *j);
void	parse_cmd_args(t_v *v, int *k);
void	copy_until(char *dest, char *source, char *delimiters, int *k);
void	parse_in_red(t_v *v, int *k, int in);
void	parse_out_red(t_v *v, int *k, int out);
void	init_struct_cmd(t_v *v);
void	ff(char *str, int *k);
void	parse_dq(char c, int *i, t_state_parse_s *state);
void	parse_sq(char c, int *i, t_state_parse_s *state);
int		fd_handler(int fd_in, int fd_out);
void	redirect_handler(t_v *v, int i, int n);
void	parse_quote_in_redirect(t_v *v, int *k, char *c);
void	add_line_to_cmd_args(t_v *v, char *src);
char	**ft_split3(char s[], char c);
int		get_pwd (t_v *v);
void	execute_command(t_v *v);
void	get_cd (t_v *v);
void	update_env_var(t_v *v, char *var);
char	*loc_var (char *var, t_v *v);
void	create_prompt(t_v *v);
void	get_echo(t_v *v, int i, int flag, int cont);
void	export_var(t_v *v, int len_arr, int i);
char	*get_var(t_v *v);
void	exc_var(t_v *v, int i, int k);
void	get_env(t_v *v);
void	exit_msh(t_v *v);
int		fork_process(t_v *v);
void	init_path(t_v *v);
int		exec_com(t_v *v);
int		set_return_status(t_v *v, int status);
void	verify_ret(t_v *v);
void	config_term(t_v *all);
int		my_termprint(int c);
void	add_hist(t_v *all, char *ret);
void	reset_flags(t_v *all);
int		count_split(char	**ret);
void	free_array(void **array);
void	check_n_free(void *ptr);
void	kill_pid(t_v *v);
int		verify_term(t_v *v, char *ret);
void	sighandler(int signum);
void	sighandlerchild(int signum);
void	add_samples(t_v *v);
void	write_error(t_v *v);
void	write_prompt(t_v *v);
void	write_return(t_v *v);
void	verify_limits(t_v *all);
void	configs(t_v *v, char **envp);
void	processing(t_v *v);
void	add_key(t_v *v);
void	dups_clear(t_v *v, char *s);
void	cleaning(t_v *v, char *s);
int		remov_quots(int i, char **aux);
void	close_fds(t_v *v, int i);
void	erase_bksp(t_v *all, int posic);
void	bye(t_v *v);
void	*safe_malloc(size_t size);
char	*get_last_path(char *ret);
void	init_cmd_args(t_v *v);
char	*get_last_path2(char *str);
int		is_abs_path(char *str);
void	reset_vpath(t_v *v);
int		exec_com2(t_v *v);

#endif
