/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:26 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/08 16:19:25 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"


// enpand $? a faire

int	built_in_echo(t_cmd *cmd)
{
    int newline;
    int i = 0;

    if (cmd->args && cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0) // le segfaulter relou
	{
		newline = 0;
		i = 1;
	}
    else
        newline = 1;
    while (cmd->args && cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        if (cmd->args[i + 1])
            if (printf(" ") < 0)
                return (1);
        i++;
    }
    if (newline == 1)
        if (printf("\n") < 0)
                return (1);
    return (0);
}