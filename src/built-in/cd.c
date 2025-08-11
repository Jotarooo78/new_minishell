/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/08 16:54:14 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// en construction

int	get_home(void)
{
	char	*path;

	path = getenv("HOME");
	if (path == NULL)
		return (1);
	if (chdir(path) == -1)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	built_in_cd(t_cmd *cmd)
{
	int	len;

	len = count_args(cmd);
	if (len > 1)
		return (perror("cd"), 1);
	else if (len == 0 || ((ft_strncmp(cmd->args[0], "~", 1) == 0 && len == 1)))
	{
		if (get_home() == 0)
			return (0);
		return (perror("cd"), 1);
	}
	// else if (ft_strncmp(cmd->args[0], "..", 2) == 0 && len == 1)
	// {
	// 	if (get_precedente_path() == 0)
	// 		return (0);
	// }
	else if (chdir(cmd->args[0]) == -1)
		return (perror("cd"), 1);
	return (0);
}
