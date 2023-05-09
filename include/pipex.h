/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:25:18 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 16:11:29 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_pipex
{
	pid_t	child1;
	pid_t	child2;
	int		infile;
	int		outfile;
	int		end[2];
	char	*cmd;
	char	*envp_path;
	char	**cmd_paths;
	char	**cmd_args;
}	t_pipex;

# define ERR_ARGS "Invalid number of arguments. args != 4.\n"

char	*get_path(char **envp);
void	get_all_path(char **envp, t_pipex *pipex);
void	get_infile(char **av, t_pipex *pipex);
void	get_outfile(char **av, t_pipex *pipex);
void	child_one(t_pipex pipex, char **av, char **envp);
void	child_two(t_pipex pipex, char **av, char **envp);
void	free_child(t_pipex *pipex, char *msg);
void	free_parent(t_pipex *pipex);
void	exit_msg_err(char *msg);

#endif
