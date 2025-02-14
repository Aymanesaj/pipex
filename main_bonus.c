/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:05:56 by asajed            #+#    #+#             */
/*   Updated: 2025/02/14 22:58:03 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		len;

	if (ac < 5)
		(ft_putstr_fd("pipex : at least 4 arguments\n", 2), exit(1));
	ft_bzero(&data, sizeof(t_pipex));
	len = ft_strlen(av[1]);
	if (len < 8)
		len = 8;
	if (!ft_strncmp(av[1], "here_doc", len))
	{
		ft_bzero(&data, sizeof(t_pipex *));
		data.env = env;
		data.av = av;
		data.cmd_count = ac - 3;
		get_path(&data);
		here_doc(&data);
	}
	else
		init_data(&data, ac, av, env);
	ft_exec(&data);
	clean_and_exit(&data, data.status, 1);
}
