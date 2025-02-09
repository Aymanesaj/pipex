/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:56:29 by asajed            #+#    #+#             */
/*   Updated: 2025/02/09 18:32:40 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*my_access(t_data *data, int idx)
{
	char	*cmd_path;
	char	*tmp;

	int (i);
	i = 0;
	if (ft_strchr(data->cmd_args[idx][0], '/'))
	{
		if (access(data->cmd_args[idx][0], X_OK) == 0)
			return (ft_strdup(data->cmd_args[idx][0]));
		else
			return (NULL);
	}
	while (data->path[i])
	{
		tmp = ft_strjoin("/", data->cmd_args[idx][0]);
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

void	get_path(t_data *data)
{
	int (j);
	j = 0;
	while (data->env[j] && ft_strncmp(data->env[j], "PATH", 4))
		j++;
	if (!data->env[j])
		ft_error("canot find the path", data, 1);
	data->path = ft_split(data->env[j] + 5, ':');
	if (!data->path)
		ft_error("problem splitting the path", data, 1);
}

void	ft_parse_args(t_data *data)
{
	data->var = 0;
	get_path(data);
	data->cmd_args = malloc(sizeof(char **) * (data->cmd_count + 1));
	if (!data->cmd_args)
		ft_error("failed to allocate", data, 1);
	while (data->av[data->var + 2] && data->var < data->cmd_count)
	{
		data->cmd_args[data->var] = ft_split(data->av[data->var + 2], ' ');
		if (!data->cmd_args[data->var])
			ft_error("problem splitting the cmd args", data, 1);
		data->cmd_args[data->var + 1] = NULL;
		data->var++;
	}
	data->cmd_paths = malloc(sizeof(char *) * (data->cmd_count + 1));
	if (!data->cmd_paths)
		ft_error("failed to allocate", data, 1);
	data->var = 0;
	while (data->cmd_args[data->var])
	{
		data->cmd_paths[data->var] = my_access(data, data->var);
		if (!data->cmd_paths[data->var])
			ft_error("access denied", data, 1);
		data->cmd_paths[data->var + 1] = NULL;
		data->var++;
	}
}

void	ft_parsing(t_data *data, int ac, char **av, char **env)
{
	ft_bzero(data, sizeof(t_data *));
	data->env = env;
	data->av = av;
	data->cmd_count = ac - 3;
	data->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->out_fd == -1)
		ft_error("failed to open or create the outfile", data, 1);
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		ft_error("No such file or directory", data, 1);
	ft_parse_args(data);
}
