/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:22:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/11 11:24:12 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	free_array(char **split)
{
	int	j;
	
	j = 0;
	if (!split)
		return ;
	while (split[j])
	{
		free(split[j]);
		j++;
	}
	free(split);
}

void	close_all_fd(int *fd)
{
	if (fd[READ] != -1)
		close(fd[READ]);
	if (fd[WRITE] != -1)
		close(fd[WRITE]);
}

void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc *tmp_h;
	
	tmp_h = NULL;
	while (heredocs)
	{
		if (heredocs->delimiter)
			free(heredocs->delimiter);
		if (heredocs->content)
			free(heredocs->content);
		if (heredocs->heredoc_fd != -1)
			close(heredocs->heredoc_fd);
		if (heredocs->next)
			tmp_h = heredocs->next;
		free(heredocs);
		heredocs = tmp_h;
	}
}

void	free_files(t_cmd *cmd)
{
	t_file *tmp;
	
	tmp = NULL;
	while (cmd->infile)
	{
		free(cmd->infile->name);
		if (cmd->infile->fd != -1)
			close(cmd->infile->fd);
		if (cmd->infile->next)
			tmp = cmd->infile->next;
		free(cmd->infile);
		cmd->infile = tmp;
	}
	while (cmd->outfile)
	{
		free(cmd->outfile->name);
		if (cmd->outfile->fd != -1)
			close(cmd->outfile->fd);
		if (cmd->outfile->next)
			tmp = cmd->outfile->next;
		free(cmd->outfile);
		cmd->outfile = tmp;
	}
	free_heredocs(cmd->heredocs);
}

void	free_all_struct(t_cmd *cmd)
{
	t_cmd *tmp;
	if (!cmd)
		return ;
	while (cmd)
	{
		free_files(cmd);
		free(cmd->name);
		free_array(cmd->args);
		if (cmd->pipefd[READ] != -1 || cmd->pipefd[WRITE] != -1)
			close_all_fd(cmd->pipefd);
		if (cmd->next)
			tmp = cmd->next;
		cmd = tmp;
	}
	free(cmd);
}

void	error(t_cmd *cmd, char *str, int code)
{
	free_all_struct(cmd);
	perror(str);
	exit(code);
}
