/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:54 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/11 11:09:31 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int built_in_exit(t_cmd *cmd, int exit_code)
{
    if (cmd->args && cmd->args[0])
    {
        if (cmd->args[1])
            return (perror("exit"), 1);
        else if (is_digit(cmd->args[0]) == 2)
            return (printf("exit: %s: Numeric argument required", cmd->args[0]), free_all_struct(cmd), 2);
        else if(is_digit(cmd->args[0]) == 0 && ft_atol(cmd->args[0]) > 255)
        {
            exit_code = ft_atol(cmd->args[0]);
            return (free_all_struct(cmd), exit(exit_code %= 2), 0);
        }
        else if (is_digit(cmd->args[0]) == 0)
        {
            exit_code = ft_atol(cmd->args[0]);
            return (free_all_struct(cmd), exit(exit_code), 0);
        }
    }
    free_all_struct(cmd);
    exit (exit_code);
    return (exit_code);
}
