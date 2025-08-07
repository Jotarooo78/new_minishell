/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/07 16:37:20 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int    get_home(void)
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

int    get_precedente_path(void)
{
    char *path;
    char **split_path;
    char *final_path;
    int i;
    
    i = 0;
    final_path = ft_strdup("");
        return (printf("here"), perror("cd"), 1);
    path = ft_strdup(getcwd(NULL, 0));
    if (path == NULL)
        return (printf("2 - i = %d\n", i), perror("cd"), 1);
    split_path = ft_split(path, '/');
    if (split_path == NULL)
        return (perror("cd"), 1);
    while (split_path[i + 1])
    {
        path = ft_strjoin(final_path, split_path[i]);
        if (final_path == NULL)
            return (printf("3.5 - i = %d\n", i), perror("cd"), 1);
        printf("3 - i = %d, final_path : %s\n", i, final_path);
        i++;
    }
    if (chdir(final_path) == -1)
    {
        free(path);
        free(final_path);
        return (printf("4 - i = %d\n", i), perror("cd"), 1);
    }
    free(path);
    free(final_path);
    return (0);
}

int	built_in_cd(t_cmd *cmd)
{
	int len;

	len = count_args(cmd);
	if (len > 1)
        return (perror("cd"), 1);
	else if (len == 0 || ((ft_strncmp(cmd->args[0], "~", 1) == 0 && len == 1)))
	{
        if (get_home() == 0)
            return (0);
        return (perror("cd"), 1);
	}
    else if (ft_strncmp(cmd->args[0], "..", 2) == 0 && len == 1)
    {
        if (get_precedente_path() == 0)
            return (0);
    }
	else
        if (chdir(cmd->args[0]) == -1)          
        return (perror("cd"), 1);
    return (0);
}
