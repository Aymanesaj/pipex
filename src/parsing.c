/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:56:29 by asajed            #+#    #+#             */
/*   Updated: 2025/02/10 19:46:08 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
			ft_free(args);
		ft_error(strerror(errno), data, 126, 1);
	}
	data->cmd_path = my_access(data, args);
	if (!data->cmd_path)
		(ft_free(args), ft_error(strerror(errno), data, exit_code(errno), 1));
	return (args);
}
