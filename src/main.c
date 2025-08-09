/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/08/09 14:33:07 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_cmd *cmd;
	t_cmd *cmd_list;

	(void)argc;
	(void)argv;
	printf("\033[2J\033[H");
	char *line;
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (line == NULL)
			break;
		add_history(line);
		cmd = parse(line);
		cmd_list = cmd;
		execute_command(cmd, cmd_list, envp);
		// condition pour le exit
		free_all_struct(cmd);
		free(line);
	}
    return (0);
}
