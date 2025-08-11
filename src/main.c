/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/08/11 15:27:25 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exit(t_cmd *cmd, int exit_status)
{
	if (!cmd)
		return ;
	if (!cmd->next && cmd->args)
	{
		if (cmd->args[0] && is_built_in(cmd))
			if (ft_strncmp(cmd->name, "exit", 4) == 0)
			{
				exit_status = built_in_exit(cmd, 0);
				exit (exit_status);
			}
	}
}

int main(int argc, char **argv, char **envp)
{
	t_cmd *cmd;
	int last_exit_status;

	(void)argc;
	(void)argv;
	printf("\033[2J\033[H");
	char *line;
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		add_history(line);
		cmd = parse(line);
		check_exit(cmd, last_exit_status);
		last_exit_status = execute_command(cmd, envp);
		free_all_struct(cmd);
		free(line);
	}
    return (0);
}
