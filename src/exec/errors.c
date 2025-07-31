/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:22:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/31 14:59:06 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"


void	free_array(char **split)
{
	int	j;
	
	j = 0;
	while (split[j])
	{
		free(split[j]);
		j++;
	}
	free(split);
}

void	free_files(t_cmd *cmd)
{
	t_file *tmp;
	t_heredoc *tmp_h;
	
	while (cmd->infile)
	{
		free(cmd->infile->name);
		tmp = cmd->infile->next;
		free(cmd->infile);
		cmd->infile = tmp;
	}
	while (cmd->outfile)
	{
		free(cmd->outfile->name);
		tmp = cmd->outfile->next;
		free(cmd->outfile);
		cmd->outfile = tmp;
	}
	while (cmd->heredocs)
	{
		free(cmd->heredocs->delimiter);
		free(cmd->heredocs->content);
		tmp_h = cmd->heredocs->next;
		free(cmd->heredocs);
		cmd->heredocs = tmp_h;
	}
}

void	free_all_struct(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		free_files(cmd);
		free(cmd->name);
		free_array(cmd->args);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	error(t_cmd *cmd, char *str, int code)
{
	free_all_struct(cmd);
	perror(str);
	exit(code);
}