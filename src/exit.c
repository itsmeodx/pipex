/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:11:26 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/13 15:02:31 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(t_list *garbage, char *msg1, char *msg2, int status)
{
	if (msg1)
	{
		if (msg2)
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", msg1, strerror(errno),
				msg2);
		else
			ft_dprintf(STDERR_FILENO, "%s: %s\n", msg1, strerror(errno));
	}
	garbage_collector(garbage);
	exit(status);
}
