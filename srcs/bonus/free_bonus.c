/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:53:56 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:15:58 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	free_double_array(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_pipes(t_pipexb *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	close_pipes(pipex);
	free(pipex->end);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
}

void	free_child(t_pipexb *pipex, char *cmd)
{
	write(2, "command not found: ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	free_double_array(pipex->cmd_args);
	free_pipes(pipex);
	free_double_array(pipex->cmd_paths);
	exit(EXIT_FAILURE);
}

void	free_parent(t_pipexb *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free_double_array(pipex->cmd_paths);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free(pipex->end);
}
