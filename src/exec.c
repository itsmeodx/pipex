/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:17:35 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/16 15:08:57 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *cmd, t_pipex *pipe_list)
{
	char	**args;
	char	*path;
	int		i;

	i = -1;
	args = ft_split(cmd, ' ');
	if (!args)
		ft_exit(pipe_list->garbage, "pipex", NULL, EXIT_FAILURE);
	ft_lstadd_back(&(pipe_list->garbage), ft_lstnew(args));
	while (args && args[++i])
		ft_lstadd_back(&(pipe_list->garbage), ft_lstnew(args[i]));
	if (access(args[0], X_OK) == 0)
		execve(args[0], args, pipe_list->envp);
	if (cmd[0] == '/' || cmd[0] == '.')
		ft_exit(pipe_list->garbage, "pipex", cmd, EXIT_FAILURE);
	i = -1;
	while (pipe_list->env_paths && pipe_list->env_paths[++i])
	{
		path = ft_strjoin(pipe_list->env_paths[i], args[0]);
		ft_lstadd_back(&(pipe_list->garbage), ft_lstnew(path));
		if (access(path, X_OK) == 0)
			execve(path, args, pipe_list->envp);
	}
	ft_exit(pipe_list->garbage, "pipex", args[0], EXIT_FAILURE);
}
