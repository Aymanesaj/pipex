/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:05:56 by asajed            #+#    #+#             */
/*   Updated: 2025/02/11 14:06:52 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	if (ac < 5)
		(ft_putstr_fd("pipex : at least 4 arguments\n", 2), exit(1));
	ft_bzero(&data, sizeof(t_pipex));
	if (!strncmp(av[1], "here_doc", 8))
		data.here_doc = 1;
	data.bonus = 1;
	init_data(&data, ac, av, env);
	if (data.here_doc)
		here_doc(&data);
	ft_exec(&data);
	clean_and_exit(&data, data.status, 1);
}
