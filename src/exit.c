/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:43:02 by asajed            #+#    #+#             */
/*   Updated: 2025/02/10 19:45:59 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	exit_code(int err)
{
	if (err == ENOENT)
		return (127);
	else if (err == EACCES)
		return (126);
	else
		return (1);
}

void	ft_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	ft_free(char **strs)
{
	int	j;

	j = 0;
	if (!strs)
		return ;
	while (strs[j])
	{
		free(strs[j]);
		j++;
	}
	if (strs)
		free(strs);
	strs = NULL;
}

void	ft_error(char *s, t_pipex *data, int status, int exit)
{
	(void)s;
	ft_putstr_fd("pipex : ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (exit)
		clean_and_exit(data, status, exit);
}

void	clean_and_exit(t_pipex *data, int status, int exit_s)
{
	ft_close(&data->fd[0]);
	ft_close(&data->fd[1]);
	ft_close(&data->in_fd);
	ft_close(&data->out_fd);
	if (data->cmd_path)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
	if (data->path)
	{
		ft_free(data->path);
		data->path = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (exit_s)
		exit(status);
}
