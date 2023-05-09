/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:25:18 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:18:31 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_pipexb
{
	pid_t	child;
	int		infile;
	int		outfile;
	int		*end;
	char	*cmd;
	char	*envp_path;
	char	**cmd_paths;
	char	**cmd_args;
	int		here_doc;
	int		nb_cmds;
	int		nb_pipes;
	int		index;
}	t_pipexb;

# define ERR_ARGS "Invalid number of arguments. Default: args > 5.\n"
# define ERR_FILES "no such file or directory"

char	*get_path(char **envp);
char	*get_cmd(char **envp_path, char *cmd);
void	get_infile(char **av, t_pipexb *pipex);
void	get_outfile(char *av_last, t_pipexb *pipex);
void	child(t_pipexb pipex, char **av, char **envp);
void	exit_msg_err(char *msg);
void	open_pipes(t_pipexb *pipex);
void	get_pipes(int ac, t_pipexb *pipex);
void	close_pipes(t_pipexb *pipex);
void	free_pipes(t_pipexb *pipex);
void	free_child(t_pipexb *pipex, char *cmd);
void	here_doc(char *av2, t_pipexb *pipex);
void	free_parent(t_pipexb *pipex);

#endif
