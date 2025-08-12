/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/08/12 20:02:47 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	void_silenced(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

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

char	**copy_env(char **envp)
{
	int i;
	char **new_env;

	i = 0;
	new_env = malloc(sizeof(char*) * (env_len(envp) + 1));
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (new_env[i] == NULL)
		{
			while (i > -1)
			{
				free(new_env[i]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int main(int argc, char **argv, char **envp)
{
	t_cmd *cmd;
	char **my_env;

	my_env = copy_env(envp);
	if (!my_env)
		return (1);
	void_silenced(argc, argv);
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
		check_exit(cmd, 0);
		execute_command(cmd, my_env);
		free_all_struct(cmd);
		free(line);
	}
    return (0);
}
