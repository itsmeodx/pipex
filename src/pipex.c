/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:11 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/16 15:10:48 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipex *pipe_list)
{
	int		p[2];

	if (pipe(p) == -1)
		ft_exit(pipe_list->garbage, "pipe", NULL, EXIT_FAILURE);
	first_child(pipe_list, p, NULL);
	second_child(pipe_list, p, NULL);
	close(p[0]);
	close(p[1]);
	while (wait(NULL) != -1)
		;
}

static int	ft_while(t_pipex *pipe_list, int *p1, int *p2)
{
	int		j;

	if (pipe_list->here_doc)
		j = 4;
	else
		j = 3;
	while (j < pipe_list->ac - 2)
	{
		pipe_list->current_cmd = pipe_list->av[j++];
		middle_child(pipe_list, p1, p2);
		close(p1[0]);
		close(p1[1]);
		p1[0] = dup(p2[0]);
		p1[1] = dup(p2[1]);
		close(p2[0]);
		close(p2[1]);
		if (j - 1 < pipe_list->ac - 3)
			if (pipe(p2) == -1)
				ft_exit(pipe_list->garbage, "pipe", NULL, EXIT_FAILURE);
	}
	return (0);
}

void	pipex_bonus(t_pipex *pipe_list)
{
	int		p1[2];
	int		p2[2];

	if (pipe(p1) == -1)
		ft_exit(pipe_list->garbage, "pipe", NULL, EXIT_FAILURE);
	if (pipe_list->here_doc)
		here_doc(pipe_list, p1);
	else
		first_child(pipe_list, p1, NULL);
	if (pipe(p2) == -1)
		ft_exit(pipe_list->garbage, "pipe", NULL, EXIT_FAILURE);
	ft_while(pipe_list, p1, p2);
	second_child(pipe_list, p1, p2);
	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);
	while (wait(NULL) != -1)
		;
}
