/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:41:36 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 16:11:54 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	get_all_path(char **envp, t_pipex *pipex)
{
	pipex->envp_path = get_path(envp);
	pipex->cmd_paths = ft_split(pipex->envp_path, ':');
	if (pipex->cmd_paths == NULL)
		exit_msg_err("ERR_MALLOC");
}
