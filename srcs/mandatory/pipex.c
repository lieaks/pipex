/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:23:48 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 16:10:41 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	exit_msg_err(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	close_pipe(t_pipex *pipex)
{
	if (close(pipex->end[0]) || close(pipex->end[1]))
		exit_msg_err("Close pipe");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		return (write(2, ERR_ARGS, ft_strlen(ERR_ARGS)), 1);
	get_infile(av, &pipex);
	get_outfile(av, &pipex);
	get_all_path(envp, &pipex);
	if (pipe(pipex.end) < 0)
	{
		free_parent(&pipex);
		exit_msg_err("Pipe");
	}
	pipex.child1 = fork();
	if (pipex.child1 == 0)
		child_one(pipex, av, envp);
	pipex.child2 = fork();
	if (pipex.child2 == 0)
		child_two(pipex, av, envp);
	close_pipe(&pipex);
	waitpid(pipex.child1, NULL, 0);
	waitpid(pipex.child2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
