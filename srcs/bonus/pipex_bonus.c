/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:23:48 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:12:54 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	right_args(char *av1, t_pipexb *pipex)
{
	if (av1 && !ft_strncmp(av1, "here_doc", 8))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int ac, char **av, char **envp)
{
	t_pipexb	pipex;

	if (ac < right_args(av[1], &pipex))
		return (write(2, ERR_ARGS, ft_strlen(ERR_ARGS)), 1);
	get_infile(av, &pipex);
	get_outfile(av[ac - 1], &pipex);
	get_pipes(ac, &pipex);
	pipex.envp_path = get_path(envp);
	pipex.cmd_paths = ft_split(pipex.envp_path, ':');
	if (pipex.cmd_paths == NULL)
	{
		free_pipes(&pipex);
		exit_msg_err("Error envp");
	}
	pipex.index = 0;
	while (pipex.index < pipex.nb_cmds)
	{
		child(pipex, av, envp);
		pipex.index++;
	}
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	free_parent(&pipex);
	return (0);
}
