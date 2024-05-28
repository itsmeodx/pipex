/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:19:18 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/15 18:32:39 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	ft_init_pipex(int ac, char **av)
{
	t_pipex	pipe_list;

	pipe_list.here_doc = 0;
	if (!strcmp(av[1], "here_doc"))
		pipe_list.here_doc = 1;
	pipe_list.file1 = av[1];
	if (pipe_list.here_doc)
		pipe_list.file1 = NULL;
	pipe_list.file2 = av[ac - 1];
	pipe_list.fd1 = 0;
	pipe_list.fd2 = 0;
	pipe_list.ac = ac;
	pipe_list.av = av;
	pipe_list.current_cmd = NULL;
	pipe_list.cmd1 = av[2];
	if (pipe_list.here_doc)
		pipe_list.cmd1 = av[3];
	pipe_list.cmd2 = av[ac - 2];
	pipe_list.env_paths = NULL;
	pipe_list.envp = NULL;
	pipe_list.limiter = av[2];
	pipe_list.garbage = NULL;
	return (pipe_list);
}
