/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/30 17:18:46 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	child_call(t_cmd *cmd, int *pipefd, char **envp)
{
    if (cmd->infile && cmd->infile->name)
        open_infile(cmd, pipefd);
	else if (cmd->outfile && cmd->outfile)
		open_outfile(cmd, pipefd);
    if (cmd->input_type == STDIN && cmd->output_type == STDOUT)
        exe_my_cmd(cmd, envp);
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

void	pipe_function(t_cmd *cmd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	while (cmd)
	{
		if (cmd->output_type == PIPEOUT)
			pipe(pipefd);
		pid = fork();
		if (pid == -1)
			error("fork failed", 1);
		if (pid == 0)
			child_call(cmd, pipefd, envp);
		else
			parent_call(cmd, pipefd);
		cmd = cmd->next;
	}
    // close(FD_STDIN);
	wait_child();
}

// void    executable(t_cmd *cmd, char **envp)
// {
//     if (cmd->input_type == STDIN && cmd->output_type == STDOUT)
//         exe_my_cmd(cmd, envp);
//     else
//         pipe_function(cmd, envp);
// }