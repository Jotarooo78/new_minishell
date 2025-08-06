/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/06 16:27:48 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	built_in_cd(t_cmd *cmd)
{
	int len;
    char *path;

	len = count_args(cmd);
	if (len > 1)
		return (1);
	else if (len == 0 || cmd->args[1] == '~')
	{
        path = ft_strdup(getenv("HOME"));
		if (path == NULL)
            return (1);
        if (chdir(path) == -1)
        {
            return (free(path), 1);
        }
	}
	// else
	// {
		
	// }
}
