/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:11 by asajed            #+#    #+#             */
/*   Updated: 2025/02/09 18:56:51 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>
#include <string.h>

void	ft_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	child_process(t_data *data, int fd_in, int i, int *pipe_fd)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_error("dup2 failed", data, 1);
	ft_close(&fd_in);
	if (i < data->cmd_count - 1)
	{
		ft_close(&pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error("dup2 failed", data, 1);
		ft_close(&pipe_fd[1]);
	}
	else
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
			ft_error("dup2 failed", data, 1);
	}
	if (execve(data->cmd_paths[i], data->cmd_args[i], data->env) == -1)
	{
		if (errno == ENOENT)
			clean_and_exit(data, 127);
		else if (errno == EACCES)
			clean_and_exit(data, 126);
		else
			clean_and_exit(data, 1);
	}
}

void	ft_exec(t_data *data)
{
	int	fd_in;

	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
		ft_error("malloc failed", data, 1);
	data->var = 0;
	fd_in = data->in_fd;
	while (data->var < data->cmd_count)
	{
		if (data->var < data->cmd_count - 1 && pipe(data->fd) == -1)
			ft_error("couldn't open a pipe", data, 1);
		data->pids[data->var] = fork();
		if (data->pids[data->var] == -1)
			ft_error("canot fork a child", data, 1);
		if (data->pids[data->var] == 0)
			child_process(data, fd_in, data->var, data->fd);
		ft_close(&fd_in);
		if (data->var < data->cmd_count - 1)
		{
			ft_close(&data->fd[1]);
			fd_in = data->fd[0];
		}
		data->var++;
	}
	data->var = 0;
	while (data->var < data->cmd_count)
	{
		waitpid(data->pids[data->var], &data->status, 0);
		if (WIFEXITED(data->status) && WEXITSTATUS(data->status) != 0)
			clean_and_exit(data, WEXITSTATUS(data->status));
		data->var++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac < 5)
		(ft_putstr_fd("pipex : at least 4 arguments\n", 2), exit(1));
	ft_bzero(&data, sizeof(t_data));
	ft_parsing(&data, ac, av, env);
	ft_exec(&data);
	clean_and_exit(&data, 0);
}
