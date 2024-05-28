/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:18:23 by oouaadic          #+#    #+#             */
/*   Updated: 2024/05/16 11:46:27 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"

# define USAGE "Usage: %s file1 cmd1 cmd2 file2\n"
# define USAGE_BONUS "Usage: %s file1 cmd1 cmd2 cmd3 ... cmdn file2\n"
# define USAGE_HERE_DOC "Usage: %s here_doc LIMITER cmd cmd1 file\n"

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
	int		ac;
	char	**av;
	char	*current_cmd;
	char	*cmd1;
	char	*cmd2;
	char	**env_paths;
	char	**envp;
	int		here_doc;
	char	*limiter;
	t_list	*garbage;
}	t_pipex;

// children.c
int		first_child(t_pipex *pipe_list, int *p1, int *p2);
int		second_child(t_pipex *pipe_list, int *p1, int *p2);
int		middle_child(t_pipex *pipe_list, int *p1, int *p2);

// env.c
char	**ft_getpath(char **envp, char *key, t_pipex *pipe_list);

// exec.c
void	execute_cmd(char *cmd, t_pipex *pipe_list);

// exit.c
void	ft_exit(t_list *garbage, char *msg1, char *msg2, int status);

// fork.c
int		ft_fork(void);

// garbage_collector.c
void	garbage_collector(t_list *garbage);

// heredoc.c
void	here_doc(t_pipex *pipe_list, int *p2);

// init.c
t_pipex	ft_init_pipex(int ac, char **av);

// open.c
int		ft_open(char *file, int flags, int mode);

// pipex.c
void	pipex(t_pipex *pipe_list);
void	pipex_bonus(t_pipex *pipe_list);

#endif // PIPEX_H
