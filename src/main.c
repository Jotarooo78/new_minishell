/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/08/11 11:32:43 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_cmd *cmd;
	int	last_exit_status;

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
		last_exit_status = execute_command(cmd, envp);
		// Pour exit, vous pouvez passer last_exit_code
		// if (cmd && ft_strncmp(cmd->name, "exit", 4) == 0)
		//     exit(last_exit_status);
		free_all_struct(cmd);
		free(line);
	}
    return (0);
}
