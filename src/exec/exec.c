/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/02 16:48:24 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

void	child_call(t_cmd *cmd, char **envp)
{
	if (cmd->heredocs)
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
	if (dup2(old_fd[READ], READ) == -1)
	{
		perror("dup error\n");
		exit(1);
	}
	if (dup2(old_fd[WRITE], WRITE) == -1)
	{
		perror("dup error\n");
		exit(1);
	}
	close(old_fd[READ]);
	close(old_fd[WRITE]);
}

void	pipe_function(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int	old_fd[2];

	if (((old_fd[0] = dup(READ)) == -1) || ((old_fd[1] = dup(WRITE)) == -1)) // 2 fd
		return (error(cmd, "dup error\n", 1));
	while (cmd)
	{
		if (cmd->heredocs)
			manage_heredocs(cmd);
		if (cmd->output_type == PIPEOUT && pipe(cmd->pipefd) == -1) // 2 fd
		{
			restaure_old_fd(old_fd);
			error(cmd, "pipe failed", 1);
		}
		pid = fork(); // nbr total de fd * nbr de fork (cmd)
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
	restaure_old_fd(old_fd);
	// close_all_fd(cmd->pipefd); // segfault
	wait_child();
}
