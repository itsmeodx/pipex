/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:19:22 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/16 11:32:06 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipe_list;

	if (ac != 5)
	{
		ft_dprintf(STDERR_FILENO, USAGE, av[0]);
		return (EXIT_FAILURE);
	}
	if (!strcmp(av[1], "here_doc") && ac < 6)
	{
		ft_dprintf(STDERR_FILENO, USAGE_HERE_DOC, av[0]);
		return (EXIT_FAILURE);
	}
	pipe_list = ft_init_pipex(ac, av);
	pipe_list.envp = envp;
	pipe_list.env_paths = ft_getpath(envp, "PATH=", &pipe_list);
	pipex(&pipe_list);
	garbage_collector(pipe_list.garbage);
	close(pipe_list.fd1);
	close(pipe_list.fd2);
	return (EXIT_SUCCESS);
}
