/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/31 16:34:50 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	open_infile(t_cmd *cmd, int *pipe_fd)
{
	int		fd;
	t_file	*file;

	file = cmd->infile;
	if (cmd->input_type == PIPEIN || cmd->output_type == PIPEOUT)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], FD_STDOUT);
		close(pipe_fd[WRITE]);
	}
	while (file && file->name)
	{
		fd = open(file->name, O_RDONLY);
		if (fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(fd, FD_STDIN);
		close(fd);
		file = file->next;
	}
}

void	open_outfile(t_cmd *cmd, int *pipe_fd)
{
	int		fd;
	t_file	*file;

	file = cmd->outfile;
	if (cmd->input_type == PIPEIN || cmd->output_type == PIPEOUT)
	{
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
	}
	while (file && file->name)
	{
		if (file->append)
			fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(fd, FD_STDOUT);
		close(fd);
		file = file->next;
	}
}

void	open_heredocs(t_cmd *cmd, int *pipe_fd)
{
	int fd;
	t_heredoc *file;

	file = cmd->heredocs;
	if (cmd->input_type == PIPEIN || cmd->output_type == PIPEOUT)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], FD_STDOUT);
		close(pipe_fd[WRITE]);
	}
	while (1)
	{
		fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			error(cmd, file->content, 1);
		}
		if (ft_strcmp(file->delimiter, file->content) == 0)
			file = file->next;
		dup2(fd, FD_STDOUT);
		close(fd);
		if (!file)
			break ;
	}
}


void	manage_here_doc(t_cmd *cmd)
{
	char *line;
	int pipefd[2];

	if (pipe(pipefd) == -1)
		error(cmd, "pipe failed\n", 1);
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(FD_STDIN);
		if (line == NULL)
			break ;
		if (compare_without_backslash(cmd, line) == true)
			break ;
		write(pipefd[WRITE], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[WRITE]);
	dup2(pipefd[READ], FD_STDIN);
	close(pipefd[READ]);
}
