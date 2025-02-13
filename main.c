/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:05:56 by asajed            #+#    #+#             */
/*   Updated: 2025/02/11 13:25:53 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	if (ac != 5)
		(ft_putstr_fd("pipex : the program takes 4 arguments\n", 2), exit(1));
	ft_bzero(&data, sizeof(t_pipex));
	init_data(&data, ac, av, env);
	ft_exec(&data);
	clean_and_exit(&data, data.status, 1);
}
