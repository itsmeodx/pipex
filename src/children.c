/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:39:54 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/16 15:11:36 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(t_pipex *pipe_list, int *p1, int *p2)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		if (p2)
		{
			close(p2[0]);
			close(p2[1]);
		}
		close(p1[0]);
		if (!pipe_list->here_doc)
			pipe_list->fd1 = ft_open(pipe_list->file1, O_RDONLY, 0);
		dup2(pipe_list->fd1, STDIN_FILENO);
		dup2(p1[1], STDOUT_FILENO);
		close(pipe_list->fd1);
		close(p1[1]);
		execute_cmd(pipe_list->cmd1, pipe_list);
	}
	return (pid);
}

int	second_child(t_pipex *pipe_list, int *p1, int *p2)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		if (p2)
		{
			close(p2[0]);
			close(p2[1]);
		}
		close(p1[1]);
		if (!pipe_list->here_doc)
			pipe_list->fd2 = ft_open(pipe_list->file2, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else
			pipe_list->fd2 = ft_open(pipe_list->file2, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		dup2(p1[0], STDIN_FILENO);
		dup2(pipe_list->fd2, STDOUT_FILENO);
		close(pipe_list->fd2);
		close(p1[0]);
		execute_cmd(pipe_list->cmd2, pipe_list);
	}
	return (pid);
}

int	middle_child(t_pipex *pipe_list, int *p1, int *p2)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		close(p1[1]);
		close(p2[0]);
		dup2(p1[0], STDIN_FILENO);
		dup2(p2[1], STDOUT_FILENO);
		close(p1[0]);
		close(p2[1]);
		execute_cmd(pipe_list->current_cmd, pipe_list);
	}
	return (pid);
}
