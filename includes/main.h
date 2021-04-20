/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 07:38:06 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:23 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN
# define MAIN
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
#include <termcap.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>

#define BUFFER_SIZE 100
#define MAX_STRING 2048

typedef struct	s_all
{
	char			**auxiliar_vet;
	int				aux_int;
	char			*pasta_atual;
	char			*local;
	long			size;
	char			**var_ambiente;
	int				tam_ambiente;
	char			**ret_split;
	char			*buf;
	char			*ret2;
	char			*ret_aux;
	int				l;
	char			ret[2048];
	char			*hist[50];
	int				qtd_hist;
	int				posic_hist;
	char			*nome_user;
	char			*cabecalho;
	int				ac;
	char			**av;
	char			**path;
	int 			var_posic;
	int				qtd_pipe;
	int				posic_pipe;
	char			**pipe_split;
	int				r_comando;
	int				pp[2];
} 	t_all;

int		execulta_comando (char *ret, t_all *all);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strpos(const char *palheiro, char agulha);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *source);
void	get_echo(char **ret, t_all *all, int fd);
void	exc_var (char **entrada, t_all *all);
void 	export_var (t_all *all, char **entrada);
void	ler_export(char **ret);
void	ls (void);
int 	get_pwd (char **ret, t_all *all, int fd);
char	*get_line(void);
void	lista_hist(t_all *all);
void	sighandler(int signum);
int		my_termprint(int c);
char	*term_get_cap(char* cap);
void	reseta_flags(t_all *all, char **env);
int		my_termprint(int c);
char	*loc_var (char **ret, char *entrada, t_all *all);
int		count_split(char	**ret);
void	atualiza_pasta(t_all *all);
void	import_ambiente(char **ret, t_all *all);
void	free_array(void **array);
void	excluir(t_all *all);
int		file_descriptor_handler(int in, int out);
#endif


