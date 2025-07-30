/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/30 13:26:24 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void    child_call(t_cmd *cmd, int *pipefd, char **envp)
{
    if (cmd->input_type == STDIN && cmd->output_type == STDOUT)
        exe_my_cmd(cmd, envp);
    if (cmd->infile->name)
        open_infile(cmd, pipefd);
    else if (cmd->outfile->name)
        open_outfile(cmd, pipefd);
    else
    {
        close(pipefd[READ]);
        dup2(pipefd[WRITE], FD_STDOUT);
        close(pipefd[WRITE]);
    }
    exe_my_cmd(cmd, envp);
}

void    parent_call(t_cmd *cmd, int *pipefd)
{
    if (cmd->input_type == PIPEIN || cmd->output_type == PIPEOUT)
    {
        close(pipefd[WRITE]);
        dup2(pipefd[READ], FD_STDIN);
        close(pipefd[READ]);
    }
}

void    wait_child()
{
    while (wait(NULL) > 0)
        ;
}

void    pipe_function(t_cmd *cmd, char **envp)
{
    int pipefd[2];
    pid_t pid;
    
    while (cmd)
    {
        if (cmd->output_type == PIPEOUT)
            pipe(pipefd);
        pid = fork();
        if (pid == -1)
			f_error("fork failed");
        // if (is_built_in(cmd->name) == false)
        //     exec_built_in(cmd, envp);
		if (pid == 0)
			child_call(cmd, pipefd, envp);
		else
			parent_call(cmd, pipefd);
		cmd = cmd->next;
    }
    wait_child();
}

// void    executable(t_cmd *cmd, char **envp)
// {
//     if (cmd->input_type == STDIN && cmd->output_type == STDOUT)
//         exe_my_cmd(cmd, envp);
//     else
//         pipe_function(cmd, envp);
// }