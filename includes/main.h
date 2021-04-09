/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 07:38:06 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/08 22:06:56 by cpereira         ###   ########.fr       */
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
} 	t_all;

void	execulta_comando (char *ret, t_all *all);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strpos(const char *palheiro, char agulha);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *source);
char	*get_cd (char **ret,t_all *all);
char	*get_echo (char **ret, t_all *all);
void	exc_var (char **entrada, t_all *all);
void 	export_var (t_all *all, char **entrada);
void	ler_export(char **ret);
void	ls (void);
char	*get_pwd (char **ret);
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
#endif


