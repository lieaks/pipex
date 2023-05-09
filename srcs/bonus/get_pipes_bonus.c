/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:56:55 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:16:23 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	open_pipes(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		if (pipe(pipex->end + (i * 2)) == -1)
		{
			free_pipes(pipex);
			exit_msg_err("Pipe");
		}
		i++;
	}
}

void	get_pipes(int ac, t_pipexb *pipex)
{
	pipex->nb_cmds = ac - pipex->here_doc - 3;
	pipex->nb_pipes = (pipex->nb_cmds - 1) * 2;
	pipex->end = malloc(pipex->nb_pipes * sizeof(int));
	if (pipex->end == NULL)
		exit_msg_err("Malloc pipe");
	open_pipes(pipex);
}

void	close_pipes(t_pipexb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_pipes)
		close(pipex->end[i++]);
}
