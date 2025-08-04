/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/04 14:06:08 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	debug_fds(const char *label)
{
	fprintf(stderr, "=== %s ===\n", label);
	for (int i = 0; i < 10; i++)
	{
		if (fcntl(i, F_GETFD) != -1)
		{
			fprintf(stderr, "FD %d: OPEN\n", i);
		}
		else
		{
			fprintf(stderr, "FD %d: CLOSED\n", i);
		}
	}
	fprintf(stderr, "==========\n");
}

void	child_call(t_cmd *cmd, char **envp, int prev_read_fd)
{
	if (cmd->heredocs && cmd->heredocs->heredoc_fd != -1)
	{
		dup2(cmd->heredocs->heredoc_fd, FD_STDIN);
		close(cmd->heredocs->heredoc_fd);
	}
	else if (cmd->infile && cmd->infile->name)
		open_infile(cmd);
	else if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, FD_STDIN);
		close(prev_read_fd);
	}
	if (cmd->outfile && cmd->outfile->name)
		open_outfile(cmd);
	else if (cmd->output_type == PIPEOUT)
	{
		close(cmd->pipefd[READ]);
		dup2(cmd->pipefd[WRITE], FD_STDOUT);
		close(cmd->pipefd[WRITE]);
	}
	exe_my_cmd(cmd, envp);
}

int	parent_call(t_cmd *cmd, int prev_read_fd)
{
	if (prev_read_fd != -1)
		close(prev_read_fd);
	if (cmd->output_type == PIPEOUT)
	{
		close(cmd->pipefd[WRITE]);
		prev_read_fd = cmd->pipefd[READ];
	}
	else
		prev_read_fd = -1;
	return (prev_read_fd);
}

void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}

void	pipe_function(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		prev_read_fd;

	prev_read_fd = -1;
	while (cmd)
	{
		if (cmd->heredocs)
			manage_heredocs(cmd);
		if (cmd->output_type == PIPEOUT && pipe(cmd->pipefd) == -1)
		{
			if (prev_read_fd != -1)
				close(prev_read_fd);
			error(cmd, "pipe failed", 1);
		}
		pid = fork();
		if (pid == -1)
		{
			if (prev_read_fd != -1)
				close(prev_read_fd);
			if (cmd->output_type == PIPEOUT)
			{
				close_all_fd(cmd->pipefd);
				error(cmd, "fork failed", 1);
			}
		}
		if (pid == 0)
			child_call(cmd, envp, prev_read_fd);
		else
			prev_read_fd = parent_call(cmd, prev_read_fd);
		cmd = cmd->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	wait_child();
}
