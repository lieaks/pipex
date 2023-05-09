/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:38:48 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 15:46:57 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	get_infile(char **av, t_pipex *pipex)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": ", 2);
		perror("");
		exit(EXIT_FAILURE);
	}
}

void	get_outfile(char **av, t_pipex *pipex)
{
	pipex->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		exit_msg_err("Outfile");
}
