/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:48:00 by asajed            #+#    #+#             */
/*   Updated: 2025/02/14 23:43:48 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "src/get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t	*pids;
	char	**av;
	char	**env;
	int		fd[2];
	int		in_fd;
	int		var;
	int		status;
	int		out_fd;
	char	*cmd_path;
	char	**path;
	int		cmd_count;
	int		is_child;
	int		nofile;
	int		nooutfile;
}			t_pipex;

char		*ft_strdup(const char *s1);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		clean_and_exit(t_pipex *data, int status, int exit_s);
void		ft_free(char **strs);
void		ft_close(int *fd);
void		ft_error(char *s, t_pipex *data, int status, int exit);
char		*my_access(t_pipex *data, char **args);
void		child_process(t_pipex *data, int fd_in, int i, int *pipe_fd);
int			exit_code(int err);
void		ft_exec(t_pipex *data);
char		**parse_data(t_pipex *data, int i);
void		get_path(t_pipex *data);
void		init_data(t_pipex *data, int ac, char **av, char **env);
void		here_doc(t_pipex *data);
void		wait_for_children(t_pipex *data);
char		**tokenize_args(char *arg);
void		open_outfile(t_pipex *data);
void		ft_bzero(void *s, size_t n);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);

#endif