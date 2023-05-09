/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:47:04 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:30:16 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	double_dup2(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

char	*get_cmd(char **envp_path, char *cmd)
{
	char	*access_cmd;

	while (*envp_path)
	{
		access_cmd = ft_join_three(*envp_path, "/", cmd);
		if (access_cmd == NULL)
			return (NULL);
		if (access(access_cmd, 0) == 0)
			return (access_cmd);
		free(access_cmd);
		envp_path++;
	}
	return (NULL);
}

void	child(t_pipexb pipex, char **av, char **envp)
{
	pipex.child = fork();
	if (pipex.child == 0)
	{
		if (pipex.index == 0)
			double_dup2(pipex.infile, pipex.end[1]);
		else if (pipex.index == pipex.nb_cmds - 1)
			double_dup2(pipex.end[(pipex.index * 2) - 2], pipex.outfile);
		else
			double_dup2(pipex.end[(pipex.index * 2) - 2],
				pipex.end[(pipex.index * 2) + 1]);
		close_pipes(&pipex);
		pipex.cmd_args = ft_split(av[pipex.index + pipex.here_doc + 2], ' ');
		if (pipex.cmd_args == NULL)
		{
			free_pipes(&pipex);
			exit_msg_err("Error malloc split");
		}
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
		if (pipex.cmd == NULL)
			free_child(&pipex, pipex.cmd_args[0]);
		execve(pipex.cmd, pipex.cmd_args, envp);
	}
}
