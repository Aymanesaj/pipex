/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:43:02 by asajed            #+#    #+#             */
/*   Updated: 2025/02/10 12:04:46 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	ft_error(char *s, t_data *data, int status, int exit)
{
	(void)s;
	ft_putstr_fd("pipex : ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (exit)
		clean_and_exit(data, status);
}

void	clean_and_exit(t_data *data, int status)
{
	int (i);
	i = 0;
	ft_close(&data->fd[0]);
	ft_close(&data->fd[1]);
	ft_close(&data->in_fd);
	ft_close(&data->out_fd);
	if (data->pids)
		free(data->pids);
	if (data->cmd_args)
	{
		while (data->cmd_args[i])
			(ft_free(data->cmd_args[i]), i++);
		free(data->cmd_args);
	}
	if (data->cmd_paths)
		ft_free(data->cmd_paths);
	if (data->path)
		ft_free(data->path);
	exit(status);
}
