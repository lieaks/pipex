/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:55:04 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:34:32 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	here_doc(char *av2, t_pipexb *pipex)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_msg_err("here_doc");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO, 0);
		if (!ft_strncmp(line, av2, ft_strlen(av2)))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	get_next_line(STDIN_FILENO, 1);
	close(fd);
	pipex->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile == -1)
	{
		unlink(".heredoc_tmp");
		exit_msg_err("here_doc");
	}
}
