/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:48:00 by asajed            #+#    #+#             */
/*   Updated: 2025/02/09 18:54:26 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "LIBFT/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	pid_t	*pids;
	char	**av;
	char	**env;
	int		fd[2];
	int		in_fd;
	int		var;
	int		status;
	int		out_fd;
	char	**cmd_paths;
	char	**path;
	char	***cmd_args;
	int		cmd_count;
}			t_data;

void		clean_and_exit(t_data *data, int status);
void		ft_free(char **strs);
void		ft_parsing(t_data *data, int ac, char **av, char **env);
void		ft_close(int *fd);
void		ft_error(char *s, t_data *data, int status);

#endif