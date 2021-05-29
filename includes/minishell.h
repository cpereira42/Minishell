/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:19:17 by user42            #+#    #+#             */
/*   Updated: 2021/05/28 19:56:56 by cpereira         ###   ########.fr       */
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

typedef enum	e_state_parse_s
{
				NORMAL,
				SINGLE_QUOTE,
				DOUBLE_QUOTE
}				t_state_parse_s;

typedef struct	s_cmd{
	char *filename;
	char **cmd_args; // filename eh o arg[0];
	int	ret_status;
	int	fd_in_red;
	int	fd_out_red;
	int	pipe[2];
	int	save_in;
	int	save_out;
	int	fd_in;
	int fd_out;
}				t_cmd;

typedef struct	s_v{
	char	**cmd_lines;
	char	**pipelines;
	char	*expanded;
	char	**env;
	t_cmd	cmd;
	char	*prompt;
	int		flag_exit;
	char	**path;

	struct	termios	term;
	struct	termios	old;
	char	*hist[50];
	//char	**hist;
	int		qtd_hist;
	int		posic_hist;
	char	*ret2;
	char	ret[2048];
	char	*name_user;
	char	*prompt1;
	int		savein;
	int		saveout;
	int		in_fd;
	int		r_command;
	int		posic_string;
	char	*aux;
	char	*path_cur;
	pid_t	pid;
	pid_t	pidc;
	char	*curr_comand;
	int		ret_last;
	int		size;
}				t_v;

void	u_print_list(t_list *list);
void	u_print_dlist(t_dlist *list);
void	prints(void *s);
void	u_free_list(t_list *list);
void	u_free_dlist(t_dlist *list);
void	prints(void *s);
int		parse_cmd_lines(t_v *v, char *linha, int p);
int		free_matrizes(char **s);
int		ft_count_lines(char **s);
void	u_free_array_bi(char **s);
int		parse_pipelines(t_v *v, char *linha);
void	u_print_array_bi(t_v *v, char **s);
int		parse_s(t_v *v, char *linha);
void	init_env(t_v *v, char **envp);
void	expand(t_v *v, char *linha, int *i, int *j);
void	parse_cmd_args(t_v *v, int *k);
void	copy_until(char *dest, char *source, char *delimiters, int *k);
void	parse_in_red(t_v *v, int *k, int in);
void	parse_out_red(t_v *v, int *k,int out);
void	u_print_struct_cmd(t_v *v);
void	init_struct_cmd(t_v *v);
void	ff(char *str, int *k);
char	**ft_split2(char const *s, char c);
void	parse_dq(char c, int *i, t_state_parse_s *state);
void	parse_sq(char c, int *i, t_state_parse_s *state);
int		fd_handler(int fd_in, int fd_out);
void	redirect_handler(t_v *v, int i, int n);
void	parse_quote_in_redirect(t_v *v, int *k, char *c);
void	add_line_to_cmd_args(t_v *v, char *src);
void	u_print_fd(void);
char	**ft_split3(char s[], char c);
int		get_pwd (t_v *v);
void	execute_command(t_v *v);
void	get_cd (t_v *v);
void	update_env_var(t_v *v, char *var);
char	*loc_var (char *var, t_v *v);
void	create_prompt(t_v *v);
void	get_echo(t_v *v);
void	export_var(t_v *v);
char	*get_var(t_v *v);
void	exc_var(t_v *v);
void	get_env(t_v *v);
void	exit_msh(t_v *v);
int		fork_process(t_v *v);
void	init_path(t_v *v);
int		exec_com(t_v *v);
int		set_return_status(t_v *v, int status);

void	reseta_flags(t_v *all);
void 	config_term(t_v *all);
int		my_termprint(int c);
void	add_hist(t_v *all, char *ret);
void	reset_flags(t_v *all);
void	update_folder(t_v *all);
int		count_split(char	**ret);
void	free_array(void **array);
void	check_n_free(void *ptr);
void	kill_pid(t_v *v);

int		verify_term(t_v *v, char *ret, int out);
int		my_termprint(int c);
void	sighandler(int signum);
void	config_term(t_v *v);
void	add_samples(t_v *v);
void	write_error(t_v *v);
void	write_prompt(t_v *v);
void	write_return(t_v *v);


void	bye(t_v *v);
void	*safe_malloc(size_t size);

void	add_hist2(t_v *v, char *ret);
void	init_hist(t_v *v, char *envp);

#endif
