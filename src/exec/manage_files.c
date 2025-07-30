/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/30 15:58:49 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	open_infile(t_cmd *cmd, int *pipe_fd)
{
	int	fd;

	if (cmd->input_type == PIPEIN || cmd->output_type == PIPEOUT)
	{		
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], FD_STDOUT);
		close(pipe_fd[WRITE]);
	}
	fd = open(cmd->infile->name, O_RDONLY);
	if (fd == -1)
	{
		error("infile opening error", 1);
	}
	dup2(fd, FD_STDIN);
	close(fd);
}

void	open_outfile(t_cmd *cmd, int *pipe_fd)
{
	int	fd;

	if (cmd->input_type == PIPEIN || cmd->output_type == PIPEOUT)
	{
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);		
	}
	fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error("outfile opening error", 1);
	}
	dup2(fd, FD_STDOUT);
	close(fd);
}