/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:58:23 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/12 19:15:33 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	garbage_collector(t_list *garbage)
{
	t_list	*tmp;

	if (!garbage)
		return ;
	while (garbage)
	{
		tmp = garbage;
		garbage = garbage->next;
		free(tmp->content);
		free(tmp);
	}
}
