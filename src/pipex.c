/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:11 by asajed            #+#    #+#             */
/*   Updated: 2025/02/14 23:27:07 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_process(t_pipex *data, int fd_in, int i, int *pipe_fd)
{
	char	*path;
	char	**args;

	data->is_child = 1;
	args = parse_data(data, i);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		(ft_free(args), ft_error(strerror(errno), data, 1, 1));
	ft_close(&fd_in);
	if (i < data->cmd_count - 1)
	{
		ft_close(&pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			(ft_free(args), ft_error(strerror(errno), data, 1, 1));
		ft_close(&pipe_fd[1]);
	}
	else
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
			(ft_free(args), ft_error(strerror(errno), data, 1, 1));
	path = ft_strdup(data->cmd_path);
	clean_and_exit(data, 0, 0);
	if (!path || execve(path, args, data->env) == -1)
	{
		(free(path), ft_free(args));
		ft_error(strerror(errno), data, exit_code(errno), 1);
	}
}

void	get_path(t_pipex *data)
{
	int (j);
	j = 0;
	while (data->env[j] && ft_strncmp(data->env[j], "PATH", 4))
		j++;
	if (!data->env[j])
		return ;
	data->path = ft_split(data->env[j] + 5, ':');
	if (!data->path)
		ft_error("problem splitting the path", data, 1, 1);
}

void	wait_for_children(t_pipex *data)
{
	data->var = 0;
	while (data->var < data->cmd_count)
	{
		waitpid(data->pids[data->var], &data->status, 0);
		if (data->nooutfile)
			data->status = 1;
		else if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else
			data->status = 1;
		data->var++;
	}
}

void	call_child(t_pipex *data, int fd_in)
{
	if (data->var == 0 && data->nofile)
		data->var++;
	child_process(data, fd_in, data->var, data->fd);
}

void	ft_exec(t_pipex *data)
{
	int	fd_in;

	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
		ft_error(strerror(errno), data, 1, 1);
	data->var = 0;
	fd_in = data->in_fd;
	while (data->var < data->cmd_count)
	{
		if (pipe(data->fd) == -1)
			ft_error(strerror(errno), data, 1, 1);
		data->pids[data->var] = fork();
		if (data->pids[data->var] == -1)
			ft_error(strerror(errno), data, 1, 1);
		if (data->pids[data->var] == 0)
			call_child(data, fd_in);
		ft_close(&fd_in);
		if (data->var < data->cmd_count - 1)
		{
			ft_close(&data->fd[1]);
			fd_in = data->fd[0];
		}
		data->var++;
	}
	wait_for_children(data);
}
