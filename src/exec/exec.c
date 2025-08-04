/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/04 11:19:25 by armosnie         ###   ########.fr       */
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

void	child_call(t_cmd *cmd, char **envp)
{
	debug_fds("BEFORE redirections");
	if (cmd->heredocs && cmd->heredocs->heredoc_fd != -1)
	{
		dup2(cmd->heredocs->heredoc_fd, FD_STDIN);
		close(cmd->heredocs->heredoc_fd);
	}
	else if (cmd->infile && cmd->infile->name)
		open_infile(cmd);
	if (cmd->outfile && cmd->outfile->name)
		open_outfile(cmd);
	else if (cmd->output_type == PIPEOUT)
	{
		close(cmd->pipefd[READ]);
		dup2(cmd->pipefd[WRITE], FD_STDOUT);
		close(cmd->pipefd[WRITE]);
	}
	debug_fds("BEFORE execve");
	exe_my_cmd(cmd, envp);
}

void	parent_call(t_cmd *cmd)
{
	if (cmd->output_type == PIPEOUT)
	{
		close(cmd->pipefd[WRITE]);
		dup2(cmd->pipefd[READ], FD_STDIN);
		close(cmd->pipefd[READ]);
	}
}

void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}

void	restaure_old_fd(int *old_fd)
{
	printf("DEBUG: Restoring fd %d->0 and fd %d->1\n", old_fd[READ],
		old_fd[WRITE]);
	if (old_fd[READ])
	{
		if (dup2(old_fd[READ], READ) == -1)
		{
			perror("dup error read\n");
			exit(1);
		}
	}
	if (old_fd[WRITE])
	{
		if (dup2(old_fd[WRITE], WRITE) == -1)
		{
			perror("dup error write\n");
			exit(1);
		}
	}
	printf("DEBUG: About to close old_fd %d and %d\n", old_fd[READ],
		old_fd[WRITE]);
	close_all_fd(old_fd);
	printf("DEBUG: old_fd closed\n");
}

void	pipe_function(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		old_fd[2];

	if (((old_fd[0] = dup(READ)) == -1) || ((old_fd[1] = dup(WRITE)) == -1))
		return (error(cmd, "dup error in pipe function\n", 1));
	while (cmd)
	{
		if (cmd->heredocs)
			manage_heredocs(cmd, old_fd);
		if (cmd->output_type == PIPEOUT && pipe(cmd->pipefd) == -1)
		{
			restaure_old_fd(old_fd);
			error(cmd, "pipe failed", 1);
		}
		pid = fork();
		if (pid == -1)
		{
			restaure_old_fd(old_fd);
			error(cmd, "fork failed", 1);
		}
		if (pid == 0)
			child_call(cmd, envp);
		else
			parent_call(cmd);
		// printf("PID parent: %d\n", getpid());
		// system("ls -la /proc/$PPID/fd/");
		cmd = cmd->next;
	}
	wait_child();
	restaure_old_fd(old_fd);
}
