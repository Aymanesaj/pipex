/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:59:35 by asajed            #+#    #+#             */
/*   Updated: 2025/02/12 10:13:22 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	free_static(char *line, int fd)
{
	int	i;

	i = 0;
	if (!line)
		line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

void	my_exec(t_pipex *data)
{
	int	fd_in;

	data->pids = malloc(sizeof(pid_t) * (data->cmd_count));
	if (!data->pids)
		ft_error(strerror(errno), data, 1, 1);
	data->var = 1;
	fd_in = data->in_fd;
	while (data->var < data->cmd_count)
	{
		if (pipe(data->fd) == -1)
			ft_error(strerror(errno), data, 1, 1);
		data->pids[data->var - 1] = fork();
		if (data->pids[data->var - 1] == -1)
			ft_error(strerror(errno), data, 1, 1);
		if (data->pids[data->var - 1] == 0)
			child_process(data, fd_in, data->var, data->fd);
		ft_close(&fd_in);
		if (data->var < data->cmd_count - 1)
		{
			ft_close(&data->fd[1]);
			fd_in = data->fd[0];
		}
		data->var++;
	}
	data->cmd_count -= 1;
	wait_for_children(data);
}

void	here_doc(t_pipex *data)
{
	char *delimiter;
	char *str;

	delimiter = ft_strjoin(data->av[2], "\n");
	ft_close(&data->out_fd);
	ft_close(&data->in_fd);
	data->in_fd = 0;
	data->in_fd = open("./here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->in_fd == -1)
		ft_error(strerror(errno), data, 1, 1);
	data->out_fd = open(data->av[data->cmd_count + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->out_fd == -1)
		ft_error(strerror(errno), data, 1, 1);
	str = get_next_line(0);
	while (str && ft_strncmp(str, delimiter, ft_strlen(str)))
	{
		write(data->in_fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
	}
	free_static(str, data->in_fd);
	free(delimiter);
	ft_close(&data->in_fd);
	data->in_fd = open("./here_doc", O_RDONLY);
	if (data->out_fd == -1)
		ft_error(strerror(errno), data, 1, 1);
	my_exec(data);
	ft_close(&data->in_fd);
	unlink("./here_doc");
	clean_and_exit(data, data->status, 1);
}
