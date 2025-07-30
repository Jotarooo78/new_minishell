/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/29 16:52:53 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	open_infile(t_cmd *cmd, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT);
	close(pipe_fd[WRITE]);
	fd = open(cmd->infile->name, O_RDONLY);
	if (fd == -1)
	{
		f_error("infile opening error");
	}
	dup2(fd, STDIN);
	close(fd);
}

void	open_outfile(t_cmd *cmd, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		f_error("outfile opening error");
	}
	dup2(fd, STDOUT);
	close(fd);
}