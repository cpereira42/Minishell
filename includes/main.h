/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 07:38:06 by cpereira          #+#    #+#             */
/*   Updated: 2021/04/06 19:42:10 by cpereira         ###   ########.fr       */
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
	char			*local;
	long			size;
	char			**var_ambiente;
	char			**ret_split;
	char			*buf;
	char			*ret2;
	int				l;
	char			ret[2048];
	char			*hist[50];
	int				qtd_hist;
	int				posic_hist;
} 	t_all;

void	execulta_comando (char *ret, t_all *all);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strpos(const char *palheiro, char agulha);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *source);
char	*get_cd (char **ret);
char	*get_echo (char **ret);
char	**exc_var (char **ret, char **entrada);
char	**get_export (char **ret, char **entrada);
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
#endif


