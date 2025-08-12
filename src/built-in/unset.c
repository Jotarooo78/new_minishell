/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:20:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/12 18:14:20 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int env_len(char **envp)
{
    char **tmp;
    int i = 0;

    tmp = envp;
    while (tmp[i])
        i++;
    return (i);
}

int    new_env(char ***envp, int target)
{
    printf("NEWENV111111111111111111111111111\n");
    int i;
    int len;
    char **new_env;

    i = 0;
    len = env_len((*envp));
    new_env = malloc(sizeof(char *) * len);
    if (!new_env)
        return (1);
    while ((*envp)[i])
    {
        if (i == target)
            i++;
        new_env[i] = ft_strdup((*envp)[i]);
        if (new_env[i] == NULL)
            return (1);
        i++;
    }
    new_env[i] = NULL;
    free_array(*envp);
    *envp = new_env;
    return (0);
}

int    find_var(t_cmd *cmd, char ***envp)
{
	int		i;
    int     j;

	i = 0;
    j = 0;
    printf("heeeeereeee\n\n\n");
	while ((*envp)[i])
	{
        if (cmd->args && cmd->args[j])
        {
            if (ft_strncmp((*envp)[i], cmd->args[j], ft_strlen(cmd->args[j])) == 0)
            {
                printf("STRNCMP111111111111111111111111111\n");
                if (new_env(envp, i) == 1)
                    return (1);
            }
            j++;
        }
		i++;
	}
    return (0);
}

int	built_in_unset(t_cmd *cmd, char ***envp)
{
    int i;

    i = 0;
    if (!cmd->args || !cmd->args[0])
        return (0);
    if (cmd->args && invalid_option(cmd, "unset"))
        return (printf("minishell: unset: '-': There is no option allowed\n"), 2);
    if (find_var(cmd, envp))
        return (1);
    return (0);
}
