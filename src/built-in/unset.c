/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:20:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/12 20:38:35 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"


// int	new_env(char ***envp, int target)
// {
// 	int		i;
//     int     j;
// 	int		len;
// 	char	**new_env;

// 	i = 0;
//     j = 0;
// 	len = env_len((*envp));
// 	new_env = malloc(sizeof(char *) * len);
// 	if (!new_env)
// 		return (1);
// 	while ((*envp)[i])
// 	{
// 		if (i == target)
// 			i++;
// 		new_env[j] = ft_strdup((*envp)[i]);
// 		if (new_env[j] == NULL)
// 			return (1);
// 		i++;
//         j++;
// 	}
// 	new_env[j] = NULL;
// 	free_array(*envp);
// 	*envp = new_env;
// 	return (0);
// }

// int	find_var(t_cmd *cmd, char ***envp)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	while (cmd->args && cmd->args[i])
// 	{
// 		len = ft_strlen(cmd->args[i]);
// 		j = 0;
// 		while ((*envp)[j])
// 		{
// 			if (ft_strncmp((*envp)[j], cmd->args[i], len - 1) == 0
// 				&& (*envp)[j][len] == '=')
// 			{
// 				printf("FOUND IT\n");
// 				if (new_env(envp, j) == 1)
// 					return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	built_in_unset(t_cmd *cmd, t_env *env);

// {
// 	int	i;

// 	i = 0;
// 	if (!cmd->args || !cmd->args[0])
// 		return (0);
// 	if (cmd->args && invalid_option(cmd, "unset"))
// 		return (printf("minishell: unset: '-': There is no option allowed\n"),
// 			2);
// 	if (find_var(cmd, env->env))
// 		return (1);
// 	return (0);
// }
