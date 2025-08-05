/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:48:50 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/05 17:22:22 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	bu_echo(t_cmd *cmd)
{
    int newline;
    int i = 1;

    if (ft_strcmp(cmd->args[1], "-n") == 0)
        newline = 0;
    else
    {
        i = 2;
        newline = 1;
    }
    while (cmd->args[i])
    {
        if (printf("%s", cmd->args[i]) < 0)
            return (1);
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

bool	is_built_in(t_cmd *cmd)
{
	if (cmd == NULL || cmd->name == NULL)
		return (false);
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (true);
	return (false);
}

int	parent_process_built_in(t_cmd *cmd, char **envp)
{
    int code_error;

    (void)envp;
    code_error = 0;
	if (ft_strcmp(cmd->name, "echo") == 0)
		code_error = bu_echo(cmd);
	// if (ft_strcmp(cmd->name, "cd") == 0)
	// 	code_error = bu_cd(cmd);
	// if (ft_strcmp(cmd->name, "pwd") == 0)
	// 	code_error = bu_pwd(cmd);
	// if (ft_strcmp(cmd->name, "export") == 0)
	// 	code_error = bu_export(cmd);
	// if (ft_strcmp(cmd->name, "unset") == 0)
	// 	code_error =  bu_unset(cmd);
	// if (ft_strcmp(cmd->name, "env") == 0)
	// 	code_error = bu_env(cmd, envp);
	// if (ft_strcmp(cmd->name, "exit") == 0)
	//     code_error = bu_exit(cmd);
    return (code_error);
}

int	child_process_built_in(t_cmd *cmd, char **envp)
{
    int code_error;

    (void)envp;
    code_error = 0;
	if (ft_strcmp(cmd->name, "echo") == 0)
		code_error = bu_echo(cmd);
	// if (ft_strcmp(cmd->name, "cd") == 0)
	// 	code_error = bu_cd(cmd);
	// if (ft_strcmp(cmd->name, "pwd") == 0)
	// 	code_error = bu_pwd(cmd);
	// if (ft_strcmp(cmd->name, "export") == 0)
	// 	code_error = bu_export(cmd);
	// if (ft_strcmp(cmd->name, "unset") == 0)
	// 	code_error =  bu_unset(cmd);
	// if (ft_strcmp(cmd->name, "env") == 0)
	// 	code_error = bu_env(cmd, envp);
	// if (ft_strcmp(cmd->name, "exit") == 0)
	//     code_error = bu_exit(cmd);
    return (code_error);
}
