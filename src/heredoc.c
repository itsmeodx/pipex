/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:11:50 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/16 18:12:25 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_while(t_pipex *pipe_list, char **line, int *i, int *j)
{
	char	*tmp1;
	char	*tmp2;
	int		len;
	int		k;

	k = -1;
	while (pipe_list->envp && pipe_list->envp[++k])
	{
		if (!ft_strncmp(pipe_list->envp[k], *line + *j, *i - *j))
		{
			tmp1 = ft_substr(*line, 0, *j - 1);
			tmp2 = tmp1;
			len = ft_strlen(pipe_list->envp[k] + *i + 2 - *j);
			tmp1 = ft_strjoin(tmp1, pipe_list->envp[k] + *i + 2 - *j);
			free(tmp2);
			tmp2 = tmp1;
			tmp1 = ft_strjoin(tmp1, *line + *i + 1);
			free(tmp2);
			free(*line);
			*line = tmp1;
			*i = *j + len - 1;
			break ;
		}
	}
}

static char	*ft_parse_line(t_pipex *pipe_list, char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[i] && ft_isalnum(line[i]))
				i++;
			i--;
			ft_while(pipe_list, &line, &i, &j);
			i--;
		}
	}
	return (line);
}

static void	print_here_doc(t_pipex *pipe_list)
{
	int		i;

	i = -1;
	while (++i < pipe_list->ac - 5)
		ft_printf("pipe ");
	ft_printf("heredoc> ");
}

void	here_doc(t_pipex *pipe_list, int *p2)
{
	char	*line;
	int		p1[2];
	int		i;

	i = -1;
	if (pipe(p1) == -1)
		ft_exit(pipe_list->garbage, "pipe", NULL, EXIT_FAILURE);
	print_here_doc(pipe_list);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, pipe_list->limiter,
			ft_strlen(pipe_list->limiter)))
	{
		line = ft_parse_line(pipe_list, line);
		ft_dprintf(p1[1], "%s", line);
		free(line);
		print_here_doc(pipe_list);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	pipe_list->fd1 = dup(p1[0]);
	close(p1[0]);
	close(p1[1]);
	first_child(pipe_list, p2, NULL);
}
