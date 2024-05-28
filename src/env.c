/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:20:15 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/15 13:06:40 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_getpath(char **envp, char *key, t_pipex *pipe_list)
{
	int		i;
	char	**env;

	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], key, 5))
			break ;
	}
	if (!envp[i])
		return (NULL);
	env = ft_split(envp[i] + 5, ':');
	ft_lstadd_back(&(pipe_list->garbage), ft_lstnew(env));
	i = -1;
	while (env && env[++i])
	{
		ft_lstadd_back(&(pipe_list->garbage), ft_lstnew(env[i]));
		env[i] = ft_strjoin(env[i], "/");
		if (!env[i])
			ft_exit(pipe_list->garbage, "ft_strjoin", NULL, EXIT_FAILURE);
		ft_lstadd_back(&(pipe_list->garbage), ft_lstnew(env[i]));
	}
	return (env);
}
