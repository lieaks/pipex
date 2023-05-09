/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:47:04 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 15:43:27 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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

void	free_child(t_pipex *pipex, char *msg)
{
	size_t	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	if (pipex->cmd)
		free(pipex->cmd);
	perror(msg);
	free_parent(pipex);
	exit(EXIT_FAILURE);
}

void	free_parent(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	child_one(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.end[1], STDOUT_FILENO);
	close(pipex.end[0]);
	dup2(pipex.infile, STDIN_FILENO);
	close(pipex.infile);
	pipex.cmd_args = ft_split(av[2], ' ');
	if (pipex.cmd_args == NULL)
		free_child(&pipex, "ERR_MALLOC");
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (pipex.cmd == NULL)
		free_child(&pipex, "ERR_CMD");
	execve(pipex.cmd, pipex.cmd_args, envp);
	free_child(&pipex, "ERR_EXEC");
}

void	child_two(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.end[0], STDIN_FILENO);
	close(pipex.end[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.outfile);
	pipex.cmd_args = ft_split(av[3], ' ');
	if (pipex.cmd_args == NULL)
		free_child(&pipex, "ERR_MALLOC");
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (pipex.cmd == NULL)
		free_child(&pipex, "ERR_CMD");
	execve(pipex.cmd, pipex.cmd_args, envp);
	free_child(&pipex, "ERR_EXEC");
}
