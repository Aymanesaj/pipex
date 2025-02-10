/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:05:56 by asajed            #+#    #+#             */
/*   Updated: 2025/02/10 19:46:04 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	init_data(t_pipex *data, int ac, char **av, char **env)
{
	ft_bzero(data, sizeof(t_pipex *));
	data->env = env;
	data->av = av;
	data->cmd_count = ac - 3;
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
	{
		data->in_fd = open("/dev/null", O_RDONLY);
		ft_error("No such file or directory", data, 1, 0);
	}
	data->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->out_fd == -1)
		ft_error(strerror(errno), data, 1, 0);
	get_path(data);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	if (ac < 5)
		(ft_putstr_fd("pipex : at least 4 arguments\n", 2), exit(1));
	ft_bzero(&data, sizeof(t_pipex));
	init_data(&data, ac, av, env);
	ft_exec(&data);
	clean_and_exit(&data, data.status, 1);
}
