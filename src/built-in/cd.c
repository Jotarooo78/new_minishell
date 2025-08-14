/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/14 20:04:12 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int get_specific_path(char *path_target)
{
	char	*path;

	path = getenv(path_target);
	if (path == NULL)
		return (1);
	if (chdir(path) == -1)
		return (1);
	return (0);
}

int	built_in_cd(t_cmd *cmd)
{
	int	len;

	len = count_args(cmd);
	if (len != 1)
		return (printf("minishell: cd..: command not found\n"),
			0);
	if (cmd->args[0][0] == '-' && cmd->args[0][1])
		return (printf("minishell: cd: '-': There is no option allowed\n"),
			2);
	if (len == 0 || ((ft_strncmp(cmd->args[0], "~", 1) == 0 && len == 1)))
	{
		if (get_specific_path("HOME") == 0)
			return (0);
		return (perror("cd: HOME:"), 1);
	}
	if ((ft_strncmp(cmd->args[0], "-", 1) == 0 && len == 1))
	{
		if (get_specific_path("OLDPWD") == 0)
			return (0);
		return (perror("cd: OLDPWD:"), 1);
	}
	if (chdir(cmd->args[0]) == -1)
		return (perror("cd: CHDIR:"), 1);
	return (0);
}


// si il y a pas eu de changement de directory avec cd, oldpwd doit etre NULL

// test a faire : enlever le OLDPWD ou HOME et voir si getenv chope la variable a partir de ma struct env ou du vrai env