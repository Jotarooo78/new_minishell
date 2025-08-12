/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:49 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/12 17:37:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int built_in_env(t_cmd *cmd, char **envp)
{
    int i;

    i = 0;
    if (!envp || !envp[i])
        return (1);
    if (invalid_option(cmd, "env") == 2)
    {
        printf("env: There is no option\n");
        return (1);
    }
    if (cmd->args && (cmd->args[0] || cmd->args[1]))
    {
        printf("env: Too many arguments\n");
        return (1);
    }
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}