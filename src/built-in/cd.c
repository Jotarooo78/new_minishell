/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/06 17:12:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int    get_env(void)
{
    char *path;

    path = ft_strdup(getenv("HOME"));
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
	int len;

	len = count_args(cmd);
	if (len > 1)
    {
        printf("Too many arguments\n");        
		return (1);
    }
	else if (len == 0 || ((ft_strncmp(cmd->args[0], "~", 1) == 0 && len == 1)))
	{
        if (get_env() == 0)
            return (0);
        else
            return (1);
	}
	else
        if (chdir(cmd->args[0]) == -1)
        {
            perror("No such file or directory");            
            return (1);
        }
    return (0);
}
