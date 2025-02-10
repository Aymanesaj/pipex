/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:48:00 by asajed            #+#    #+#             */
/*   Updated: 2025/02/10 19:45:01 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "LIBFT/libft.h"
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
}			t_pipex;

void		clean_and_exit(t_pipex *data, int status, int exit_s);
void		ft_free(char **strs);
void		ft_close(int *fd);
void		ft_error(char *s, t_pipex *data, int status, int exit);
char		*my_access(t_pipex *data, char **args);
void		child_process(t_pipex *data, int fd_in, int i, int *pipe_fd);
int			exit_code(int err);
void		ft_exec(t_pipex *data);
char		**parse_data(t_pipex *data, int i);

#endif