/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/11 11:41:47 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// void	debug_fds(const char *label)
// {
// 	fprintf(stderr, "=== %s ===\n", label);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		if (fcntl(i, F_GETFD) != -1)
// 		{
// 			fprintf(stderr, "FD %d: OPEN\n", i);
// 		}
// 		else
// 		{
// 			fprintf(stderr, "FD %d: CLOSED\n", i);
// 		}
// 	}
// 	fprintf(stderr, "==========\n");
// }

void	child_call(t_cmd *cmd, t_cmd *cmd_list, char **envp, int prev_read_fd)
{
	int exit_status;
	
	if (is_built_in(cmd))
	{
		exit_status = child_process_built_in(cmd, envp);
		exit(exit_status);
	}
	unused_heredoc_fd(cmd, cmd_list);
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

int	wait_child(pid_t *pid, int size)
{
	int i;
	int status;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	return (status);
}

void	pipe_check_or_create(t_cmd *cmd, int prev_read_fd)
{
	if (cmd->output_type == PIPEOUT && pipe(cmd->pipefd) == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		error(cmd, "pipe failed", 1);
	}
}

void	pidarray_check(t_cmd *cmd, pid_t *pid, int prev_read_fd, int i)
{
	if (pid[i] == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (cmd->output_type == PIPEOUT)
		{
			close_all_fd(cmd->pipefd);
			error(cmd, "fork failed", 1);
		}
	}
}

int	pipe_function(t_cmd *cmd, pid_t *pid, int exit_status, char **envp)
{
	t_cmd *cmd_list;
	int		prev_read_fd;
	int		i;

	i = 0;
	prev_read_fd = -1;
	cmd_list = cmd;
	while (cmd && i < MAX_PROCESSES)
	{
		if (cmd->heredocs)
			manage_heredocs(cmd);
		pipe_check_or_create(cmd, prev_read_fd);
		pid[i] = fork();
		pidarray_check(cmd, pid, prev_read_fd, i);
		if (pid[i] == 0)
			child_call(cmd, cmd_list, envp, prev_read_fd);
		else
			prev_read_fd = parent_call(cmd, prev_read_fd);
		i++;
		cmd = cmd->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	exit_status = wait_child(pid, i);
	return (exit_status);
}

int execute_command(t_cmd *cmd, char **envp)
{
	pid_t pid[MAX_PROCESSES];
	int exit_status;
	
	if (!cmd)
		return (0);
	exit_status = 0;
	ft_memset(pid, 0, sizeof(pid));
	if (is_built_in(cmd))
	{
		if (cmd->output_type != PIPEOUT && !cmd->next)
			exit_status = pipe_function(cmd, pid, exit_status, envp);
		else
		{
			if (cmd && ft_strncmp(cmd->name, "exit", 4) == 0)
				built_in_exit(cmd, exit_status);
		}
	}
	else
		exit_status = pipe_function(cmd, pid, exit_status, envp);
	return (exit_status);
}
