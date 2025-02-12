/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:56:29 by asajed            #+#    #+#             */
/*   Updated: 2025/02/12 09:47:44 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_data(t_pipex *data, int ac, char **av, char **env)
{
	ft_bzero(data, sizeof(t_pipex *));
	data->env = env;
	data->av = av;
	data->cmd_count = ac - 3;
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		ft_error(strerror(errno), data, 1, 0);
	data->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->out_fd == -1)
		ft_error(strerror(errno), data, 1, 1);
	get_path(data);
}

char	*my_access(t_pipex *data, char **args)
{
	char	*cmd_path;
	char	*tmp;

	int (i);
	i = 0;
	if (!data->path || ft_strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
			return (ft_strdup(args[0]));
		else
			return (NULL);
	}
	while (data->path[i])
	{
		tmp = ft_strjoin("/", args[0]);
		cmd_path = ft_strjoin(data->path[i], tmp);
		free(tmp);
		if (access(cmd_path, X_OK) == -1)
			free(cmd_path);
		else
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	**parse_data(t_pipex *data, int i)
{
	char	**args;

	args = ft_split(data->av[i + 2], ' ');
	if (!args || !args[0])
	{
		if (args)
			ft_free(args), ft_error("command not found", data, 126, 1);
		ft_error(strerror(errno), data, 126, 1);
	}
	data->cmd_path = my_access(data, args);
	if (!data->cmd_path)
		(ft_free(args), ft_error(strerror(errno), data, exit_code(errno), 1));
	return (args);
}
