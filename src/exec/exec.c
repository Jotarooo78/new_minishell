/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/31 15:03:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	child_call(t_cmd *cmd, int *pipefd, char **envp)
{
	if (cmd->infile && cmd->infile->name)
		open_infile(cmd, pipefd);
	else if (cmd->outfile && cmd->outfile->name)
		open_outfile(cmd, pipefd);
	else
	{
		close(pipefd[READ]);
		dup2(pipefd[WRITE], FD_STDOUT);
		close(pipefd[WRITE]);
	}
	exe_my_cmd(cmd, envp);
}

void	parent_call(t_cmd *cmd, int *pipefd)
{
	if (cmd->output_type == PIPEOUT)
	{
		close(pipefd[WRITE]);
		dup2(pipefd[READ], FD_STDIN);
		close(pipefd[READ]);
	}
}

void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}

void	restaure_old_fd(int *old_fd)
{
	if ((dup2(old_fd[READ], READ) == -1) || dup2(old_fd[WRITE], WRITE) == -1)
	{
		perror("dup error\n");
	}
}

void	pipe_function(t_cmd *cmd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		old_fd[2];
	
	if (((old_fd[0] = dup(READ)) == -1) || ((old_fd[1] = dup(WRITE)) == -1))
		return (error(cmd, "dup error\n", 1));
	while (cmd)
	{
		if (cmd->output_type == PIPEOUT)
			pipe(pipefd);
		pid = fork();
		if (pid == -1)
			error(cmd, "fork failed", 1);
		if (pid == 0)
			child_call(cmd, pipefd, envp);
		else
			parent_call(cmd, pipefd);
		cmd = cmd->next;
	}
	wait_child();
	restaure_old_fd(old_fd);
}
