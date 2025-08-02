/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/02 16:22:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

void	open_infile(t_cmd *cmd)
{
	t_file	*file;

	file = cmd->infile;
	// if (cmd->output_type == PIPEOUT)
	// {
	// 	close(cmd->pipefd[READ]);
	// 	dup2(cmd->pipefd[WRITE], FD_STDOUT);
	// 	close(cmd->pipefd[WRITE]);
	// }
	while (file && file->name)
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(file->fd, FD_STDIN);
		close(file->fd);
		file = file->next;
	}
}

void	open_outfile(t_cmd *cmd)
{
	t_file	*file;

	file = cmd->outfile;
	// if (cmd->output_type == PIPEOUT)
	// {
	// 	close(cmd->pipefd[READ]);
	// 	close(cmd->pipefd[WRITE]);
	// }
	while (file && file->name)
	{
		if (file->append)
			file->fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file->fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(file->fd, FD_STDOUT);
		close(file->fd);
		file = file->next;
	}
}

void	child_process_heredoc(t_cmd *cmd, t_heredoc *heredoc)
{
	char	*line;

	while (1)
	{
		line = readline("\033[36mheredoc> \033[0m");
		if (line == NULL)
			exit(0);
		if (ft_strncmp(heredoc->delimiter, line, ft_strlen(line)) == 0)
			break ;
		write(cmd->pipefd[WRITE], line, ft_strlen(line));
		write(cmd->pipefd[WRITE], "\n", 1);
		free(line);
	}
	close(cmd->pipefd[READ]);
	close(cmd->pipefd[WRITE]);
	free(line);
	exit(0);
}

void	parent_process_heredoc(t_cmd *cmd, pid_t pid)
{
	int	status;

	close(cmd->pipefd[WRITE]);
	waitpid(pid, &status, 0);
}

void	manage_heredocs(t_cmd *cmd)
{
	t_heredoc	*heredoc;
	pid_t		pid;
	int			tmp_pipe[2];

	heredoc = cmd->heredocs;
	while (heredoc)
	{
		if (pipe(tmp_pipe) == -1)
			error(cmd, "pipe failed\n", 1);
		cmd->pipefd[READ] = tmp_pipe[READ];
		cmd->pipefd[WRITE] = tmp_pipe[WRITE];
		pid = fork();
		if (pid == -1)
		{
			close(tmp_pipe[READ]);
			close(tmp_pipe[WRITE]);
			error(cmd, "fork failed", 1);
		}
		if (pid == 0)
			child_process_heredoc(cmd, heredoc);
		else
		{
			parent_process_heredoc(cmd, pid);
			if (heredoc->heredoc_fd != -1)
				close(heredoc->heredoc_fd);
			heredoc->heredoc_fd = cmd->pipefd[READ]; // quand fermer ce fd correctement ?
		}
		
		heredoc = heredoc->next;
		// if (heredoc->next)
		// 	close(heredoc->heredoc_fd);
		// close(cmd->pipefd[READ]); // boucle infini
	}
		cmd->pipefd[READ] = -1;
		cmd->pipefd[WRITE] = -1;
}
